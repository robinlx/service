//
//
//
//  @ Project : Log
//  @ File Name : FileLog.cpp
//  @ Date : 2012/5/4
//  @ Author : 
//
//
#include "stdafx.h"
#include "FileLog.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <vector>
#include <algorithm>
#ifdef WIN32
#include <windows.h>
#else
#include <fnmatch.h>
#include <dirent.h>
#endif // WIN32

#include "common/Define.h"
#include <string.h>
#include <iostream>
using namespace std;


const int MAX_BUFF_SIZE = 1024;


FileLog::FileLog( const std::string& fileName, int fileSize, int fileCount, int lvMask )
	:LogEngine(lvMask), m_FileName(fileName), m_FileSize(fileSize * 1024 * 1024), m_FileCount(fileCount), m_LogFile(NULL)
{
	base::m_Type = ENG_FILE;
    m_Buff = new std::stringstream;
	m_ThreadSign = true;
    this->OpenFile();
	
}


FileLog::~FileLog()
{
	ACE_Thread::join(m_ThreadHandle);
	this->FlushBuffList(true);
	
	
	if (m_LogFile)
	{
		fclose(m_LogFile);
		m_LogFile = NULL;
	}
	
}

void FileLog::WriteLog( const LogMsg& msg )
{
    //检查日志类型与级别
	if (!(msg.Engines & ENG_FILE) || !(msg.Levels & m_LogLevels))
	{
		return;
	}

	m_Mutex.acquire();

    //写入到缓存
    (*m_Buff) << msg.LogStr();

    //缓存达到最大值时刷新缓存
    if (m_Buff->str().size() >= MAX_BUFF_SIZE)
    {
        m_BuffList.push_back(m_Buff);
        m_Buff = new std::stringstream();
		ACE_Thread::spawn((ACE_THR_FUNC)ThreadFun, this, THR_NEW_LWP|THR_JOINABLE, 0, &m_ThreadHandle);
    }

	m_Mutex.release();
}

unsigned int FileLog::OpenFile()
{
    this->makeFilePath();

	if (m_LogFile == NULL)
	{
		m_LogFile = ACE_OS::fopen(m_FileName.c_str(), "a+t");
	}

    if (m_LogFile == NULL)
    {
        Logger::Error("Failed to open log file.");
        return -1;
    }
	//判断文件大小
	unsigned int size = ACE_OS::ftell(m_LogFile);
 	if (size >= (unsigned)m_FileSize)
	{
		fclose(m_LogFile);
		m_LogFile = NULL;

		DoRotate();

		m_LogFile = ACE_OS::fopen(m_FileName.c_str(), "a+t");
		size = ACE_OS::ftell(m_LogFile);
	}

	return size;
}

void FileLog::DoRotate()
{
	// recheck file size
	struct stat fs;
	memset(&fs, 0, sizeof(fs));
	if ((::stat(m_FileName.c_str(), &fs) != 0) || (fs.st_size < m_FileSize)) 
		return ;

	char szBuffer[256] = {'\0'};
	std::string strDir = m_FileName.substr(0, m_FileName.rfind(PATH_SEPARATOR) + 1);
	std::string strFileName = m_FileName.substr(m_FileName.rfind(PATH_SEPARATOR) + 1);

	std::vector<_LOG_FileItem> fileList;
	BuildFileList(&fileList, strDir, strFileName);


	for (int i = fileList.size() - m_FileCount; i >= 0 ; --i)
	{
		if (strDir.empty())
		{
			ACE_OS::strcpy(szBuffer, fileList[i].Name.c_str());
		}
		else
		{
			ACE_OS::sprintf(szBuffer, "%s%c%s", strDir.c_str(), PATH_SEPARATOR, fileList[i].Name.c_str());
		}

		remove(szBuffer);
	}

	//changename
	time_t curtime = time(NULL);
	char sztime[16];
	ACE_OS::strftime(sztime, 256, "%Y%m%d.%H%M", ACE_OS::localtime(&curtime));
	ACE_OS::sprintf(szBuffer, "%s_%s", m_FileName.c_str(), sztime);
	rename(m_FileName.c_str(), szBuffer);
	return;
}

const std::string& FileLog::LogName() const
{
	return m_FileName;
}


bool _SortByCreateTime(FileLog::_LOG_FileItem first, FileLog::_LOG_FileItem second)
{
	return first.CTime > second.CTime;
}


void FileLog::BuildFileList( std::vector<_LOG_FileItem>* fileList, const std::string& dir, const std::string& filename )
{
#ifdef WIN32 
	HANDLE hFile=NULL; 
	char szBuffer[MAX_PATH] = {NULL}; 
	WIN32_FIND_DATA wfs = {NULL}; 
	ACE_OS::sprintf(szBuffer, "%s%s_????????.????", dir.c_str(), filename.c_str()); 
	hFile= FindFirstFile(szBuffer, &wfs);
	while( NULL != hFile && INVALID_HANDLE_VALUE != hFile ) 
	{ 
		if (!(wfs.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) 
		{ 
			_LOG_FileItem item; 
			ULARGE_INTEGER ull; 
			ull.LowPart = wfs.ftCreationTime.dwLowDateTime; 
			ull.HighPart = wfs.ftCreationTime.dwHighDateTime; 
			item.CTime = ull.QuadPart / 10000000ULL - 11644473600ULL; 
			item.Name = wfs.cFileName; 
			fileList->push_back(item); 
		} 
 
		if (!FindNextFile(hFile, &wfs)){   
			if (ERROR_NO_MORE_FILES == GetLastError()) {break;} 
		} 
	} 
	FindClose(hFile); 
#else 
	DIR *pdir;
	struct dirent *pdirent;
	char temp[256];
	char pattern[256] = {'\0'};
	sprintf(pattern, "%s_????????.????", filename.c_str());
	sprintf(temp, "%s", dir.empty()? "./": dir.c_str());
	pdir = opendir(temp);
	if(pdir != NULL)
	{

		while(pdirent = readdir(pdir))
		{
			int res = fnmatch(pattern, pdirent->d_name, FNM_PERIOD|FNM_PATHNAME);
			if(res != 0)
				continue;

			sprintf(temp, "%s%s", dir.c_str(), pdirent->d_name);
			struct stat st;
			lstat(temp, &st);
			if ( S_ISDIR(st.st_mode) )
			{
				continue;
			}
			_LOG_FileItem item;
			item.CTime = st.st_ctime;
			item.Name = pdirent->d_name;
			fileList->push_back(item);
		}
	}
	closedir(pdir);
	std::sort(fileList->begin(), fileList->end(), _SortByCreateTime);
#endif  //WIN32
}


void* FileLog::ThreadFun(void* fileLog)
{
    FileLog* pthis = static_cast<FileLog*>(fileLog);
    pthis->FlushBuffList();
    return 0;
}
    
void FileLog::FlushBuffList(bool isAll /*= false*/)
{
	//获取文件大小
	unsigned int size = this->OpenFile();
    if (size == -1)
    {
        return ;
    }
	
    BuffList::iterator iter = m_BuffList.begin(); 
    while(iter != m_BuffList.end())
    {
        //写入Log
		fwrite((*iter)->str().c_str(), (*iter)->str().size(), sizeof(char), m_LogFile);
		size += (*iter)->str().size();

        //写满时开启新的文件
		if (size >= static_cast<unsigned int>(m_FileSize))
		{
			size = this->OpenFile();
		}
		
		m_Mutex.acquire();
		iter = m_BuffList.erase(iter);
		m_Mutex.release();
    }

    if (isAll)
    {
        m_Mutex.acquire();
        fwrite(m_Buff->str().c_str(), m_Buff->str().size(), sizeof(char), m_LogFile);
        m_Mutex.release();

    }
    

}

void FileLog::makeFilePath()
{
    std::string libpath = m_FileName;
    if (ACE_OS::access(libpath.c_str(), 0) != 0)
    {
        std::string::size_type pos = libpath.find(PATH_SEPARATOR,3);
        while(pos != std::string::npos)
        {
#ifdef WIN32
            ACE_OS::mkdir(libpath.substr(0, pos).c_str());
#else 
            mkdir(libpath.substr(0, pos).c_str(), S_IRWXU|S_IRWXG|S_IROTH);
#endif
            pos = libpath.find(PATH_SEPARATOR, pos + 1);
        }
    }
}




