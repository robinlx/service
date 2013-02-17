//////////////////////////////////////
//File: WindowsEntrance.cpp
//Author:   Robin.L
//Date:     2013.2.7
//Description:
//  windows���������������ڷ������������������ʼ���ȹ���,windows���������
/////////////////////////////////////



#include "stdafx.h"


#include "WindowsEntrance.h"
#include <ace/Get_Opt.h>
#include "Config.h"
#include "logger/EngineMaker.h"
#include "WinService.h"
#include "IDaemon.h"

WindowsEntrance::WindowsEntrance(void)
{
    m_Insert = m_Remove = m_Start = m_Kill = m_Run = false;
    m_Deamon = NULL;
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
    try
    {
        this->initPath();

        this->initConfig();

        this->initLog();
    }
    catch (Exception* e)
    {
        stringstream stream;
        stream << "Initialize running environment invalidly." << std::endl
            << e->message();
        Logger::Error(stream.str());
        Logger::Debug(e->tostr());
    }
    catch (...)
    {
        stringstream stream;
        stream << "Initialize running environment invalidly with unknown exception." << std::endl;
        Logger::Error(stream.str());
    }
    

    try
    {
        //����̨����
        if (m_Debug)
        {
            m_Deamon = IDaemon::CreateInstance(IDaemon::SRV_Consoles);
            m_Deamon->Start();
            return 0;
        }

        m_Deamon = IDaemon::CreateInstance(IDaemon::SRV_Service);
        if (m_Deamon == NULL)
        {
            throw Exception("Failed to create IDaemon object and IDaemon object is NULL");
        }
        //��װϵͳ����
        if (m_Insert && !m_Remove)
        {
            m_Deamon->Setup();
            return 0;
        }

        //�Ƴ�ϵͳ����
        if (m_Remove && !m_Insert)
        {
            m_Deamon->Remove();
            return 0;
        }

        //��������
        if (m_Start && !m_Kill)
        {
            m_Deamon->Start();
            return 0;
        }

        //ֹͣ����
        if (m_Kill && ! m_Start)
        {
            m_Deamon->Stop();
            return 0;
        }
        
        //���У�ϵͳ��������ʱ���ɷ�����������ã�
        if (m_Run)
        {
            m_Deamon->Run();
            return 0;
        }
    }
    catch(Exception *e)
    {
        Logger::Error(e->message());
        Logger::Debug(e->tostr());
        return 3;
    }
    catch(...)
    {
        Logger::Error("Run service failed with unknown exception");
        return 3;
    }


    this->printUsage();

    return 2;
}

void WindowsEntrance::printUsage()
{
    cout << "Application: " << APP_NAME << " Version: " << APP_VERSION << endl 
        << "Usage: " << APP_NAME << " [options]" << endl
        << "Run IPBC service with options" << endl
        << "-i:\tInsert " << APP_NAME << " into windows service manager;" << endl
        << "-r:\tRemove " << APP_NAME << " from windows service manager;" << endl
        << "-s:\tStart " << APP_NAME << ";" << endl
        << "-k:\tKill/Stop " << APP_NAME << ";" << endl
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
        char confPath[MAX_PATH] = {0};
        ACE_OS::snprintf(confPath, MAX_PATH, "%s\\conf\\%s.conf", workPath, APP_NAME);
        m_ConfigPath = confPath;
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
        char tmpLogPath[MAX_PATH] = {0};
        ACE_OS::snprintf(tmpLogPath, MAX_PATH, "%s\\log\\%s.log", workPath, APP_NAME);
        logPath = tmpLogPath;
    }
    
    EngineMaker::MakeFileEngine(logPath, 
        SVR_CONF::instance()->getLogInfo()->Size, 
        SVR_CONF::instance()->getLogInfo()->Backup, lv);
}

void WindowsEntrance::exit()
{
    m_Deamon->Stop();
}
