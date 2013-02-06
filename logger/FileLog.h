//
//
//
//  @ Project : Log
//  @ File Name : FileLog.h
//  @ Date : 2012/5/4
//  @ Author : 
//
//


#if !defined(_COMTOM_V3_COMMON_FILELOG_H_)
#define _COMTOM_V3_COMMON_FILELOG_H_

#include <string>
#include <fstream>
#include <vector>
#include "LogEngine.h"
#include <sstream>
#include <list>
#include <ace/Thread.h>
#include <ace/Thread_Mutex.h>

class FileLog : public LogEngine
{
	typedef LogEngine base;
public:
	FileLog(const std::string& fileName, int fileSize, int fileCount, int lvMask);
	virtual ~FileLog();

	virtual void WriteLog(const LogMsg& msg);

	const std::string& LogName() const;

	virtual bool operator==(const LogEngine& obj) const
	{
		return base::m_Type == obj.Type() && m_FileName == static_cast<const FileLog&>(obj).LogName();
	}

	struct _LOG_FileItem
	{
		time_t CTime;	//Create time;
		std::string Name;
	};

protected:
	unsigned int OpenFile();
	void DoRotate();
	void BuildFileList(std::vector<_LOG_FileItem>* fileList, const std::string& dir, const std::string& filename);

    static void* ThreadFun(void* fileLog);
    void FlushBuffList();
protected:
	std::string		m_FileName;
	long        	m_FileSize;		//单位byte
	int				m_FileCount;	//备份日志文件数量
	FILE*			m_LogFile;
    
    typedef std::list<std::stringstream*> BuffList;
    std::stringstream*  m_Buff;
    BuffList            m_BuffList;
    ACE_hthread_t       m_ThreadHandle;
	bool				m_ThreadSign;

	ACE_Thread_Mutex	m_Mutex;
};

#endif  //_COMTOM_V3_COMMON_FILELOG_H_
