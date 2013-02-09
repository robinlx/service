//////////////////////////////////////
//File: WindowsEntrance.cpp
//Author:   Robin.L
//Date:     2013.2.7
//Description:
//  windows���������������ڷ������������������ʼ���ȹ���,windows���������
/////////////////////////////////////



#include "stdafx.h"
#include <ace/Get_Opt.h>
#include "WindowsEntrance.h"
#include "Config.h"
#include "logger/EngineMaker.h"
#include "WinService.h"

WindowsEntrance::WindowsEntrance(void)
{
    m_Insert = m_Remove = m_Start = m_Kill = m_Run = false;
}

WindowsEntrance::~WindowsEntrance(void)
{
}

void WindowsEntrance::init( int argc, char **argv )
{
    //�����������
    ACE_OS::strcpy(m_AppName, argv[0]);

    //��������
    const char options[] = "hirskdxc:";
    ACE_Get_Opt cmd(argc, argv, options,  1, 0, ACE_Get_Opt::PERMUTE_ARGS, 1);

    //TODO:���ó���������ʧ��
    cmd.long_option(ACE_TEXT("help"), 'h', ACE_Get_Opt::ARG_REQUIRED);
    cmd.long_option(ACE_TEXT("insert"), 'i', ACE_Get_Opt::ARG_REQUIRED);
    cmd.long_option(ACE_TEXT("remove"), 'r', ACE_Get_Opt::ARG_REQUIRED);
    cmd.long_option(ACE_TEXT("start"), 's', ACE_Get_Opt::ARG_REQUIRED);
    cmd.long_option(ACE_TEXT("kill"), 'k', ACE_Get_Opt::ARG_REQUIRED);
    cmd.long_option(ACE_TEXT("debug"), 'd', ACE_Get_Opt::ARG_REQUIRED);
    cmd.long_option(ACE_TEXT("config"), 'x', ACE_Get_Opt::ARG_REQUIRED);
    cmd.long_option(ACE_TEXT("config"), 'c', ACE_Get_Opt::ARG_REQUIRED);
    
    int opt = 0;
    while((opt = cmd()) != EOF)
    {
        switch(opt)
        {
        case 'x':
            m_Run = true;
            break;
        case 'h':
            m_Help = true;
            break;
        case 'd':
            m_Debug = true;
            break;
        case 'c':           //����Ϊconfigʱ����ȡ�����������ļ�����
            m_Config = true;
            m_ConfigPath = cmd.opt_arg();
            if (m_ConfigPath.empty())
            {
                m_Help = true;
            }
            break;
        case 'i':
            m_Insert = true;
            break;
        case 'r':
            m_Remove = true;
            break;
        case 's':
            m_Start = true;
            break;
        case 'k':
            m_Kill = true;
            break;
        default:
            m_Help = true;
            break;
        }
    }
}

int WindowsEntrance::entry()
{
    if (m_Help)
    {
        this->printUsage();
        return 0;
    }

    //��ʼ������·���������ļ�·����
    this->initPath();

    this->initConfig();

    this->initLog();

    //����̨����
    if (m_Debug)
    {
        
    }

    //��װϵͳ����
    if (m_Insert && !m_Remove)
    {
        SERVICE::instance()->Setup();
    }

    //�Ƴ�ϵͳ����
    if (m_Remove && !m_Insert)
    {
        SERVICE::instance()->Remove();
    }

    //��������
    if (m_Start && !m_Kill)
    {
        SERVICE::instance()->Start();
    }

    //ֹͣ����
    if (m_Kill && ! m_Start)
    {
        SERVICE::instance()->Stop();
    }
    
    //���У�ϵͳ��������ʱ���ɷ�����������ã�
    if (m_Run)
    {
        SERVICE::instance()->Run();
    }
    


    this->printUsage();

    return 2;
}

void WindowsEntrance::printUsage()
{
    cout << "Usage: IPBCService [options]" << endl
        << "Run IPBC service with options" << endl
        << "-i:\tInsert IPBCService into windows service manager;" << endl
        << "-r:\tRemove IPBCService from windows service manager;" << endl
        << "-s:\tStart IPBCService;" << endl
        << "-k:\tKill/Stop IPBCService;" << endl
        << "-d:\tRun servece with debug mode;" << endl
        << "-c <ConfigFile>: Specified config file;" << endl
        << "-h:\tShow the help info and exit." << endl;
}

void WindowsEntrance::initPath()
{
    char workPath[MAX_PATH]={0};
    //���ù���·��
    if (GetModuleFileName(GetModuleHandle(NULL), workPath, MAX_PATH) != 0)
    {
        char *tmp = ACE_OS::strrchr(workPath, '\\');
        *tmp = '\0';
        ACE_OS::chdir(workPath);
    }
    
    //���������ļ�·��,Ĭ�������ļ�·��Ϊ����·�������·��../conf/IPBCService.conf
    if (m_Config == false)
    {
        ACE_OS::strcpy(workPath, getcwd(NULL, 0));    
        char *tmp = ACE_OS::strrchr(workPath, '\\');
        *tmp = '\0';
        m_ConfigPath = workPath;
        cout << m_ConfigPath << endl;
        m_ConfigPath += "\\conf\\IPBCService.conf";
    }
}

void WindowsEntrance::initConfig()
{
    SVR_CONF::instance()->init(m_ConfigPath); 
}

void WindowsEntrance::initLog()
{
    LevelsMask lv = LEV_INFO|LEV_ERROR;
    if (SVR_CONF::instance()->getLogInfo()->Debug)
    {
        lv = lv | LEV_DEBUG;
    }
    
    if (!m_Run)
    {
        EngineMaker::MakeConsoleEngine(lv);
    }
    
    std::string logPath = SVR_CONF::instance()->getLogInfo()->Path;
    if (logPath.empty())
    {
        char workPath[MAX_PATH]={0};
        ACE_OS::strcpy(workPath, getcwd(NULL, 0));    
        char *tmp = ACE_OS::strrchr(workPath, '\\');
        *tmp = '\0';
        logPath = workPath;
        logPath += "//log//IPBCService.log";
    }
    
    EngineMaker::MakeFileEngine(logPath, 
        SVR_CONF::instance()->getLogInfo()->Size, 
        SVR_CONF::instance()->getLogInfo()->Backup, lv);
}
