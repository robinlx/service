//////////////////////////////////////
//File: LinuxEntrance.cpp
//Author:   Robin.L
//Date:     2013.1.25
//Description:
//  服务入口类程序，用于分析程序参数，基本初始化等工作
/////////////////////////////////////



#include "stdafx.h"

#ifndef WIN32
#include "LinuxEntrance.h"

#include <ace/Get_Opt.h>
#include "Config.h"
#include "logger/EngineMaker.h"
#include "IDaemon.h"


LinuxEntrance::LinuxEntrance()
{
    base::m_Help = false;
    base::m_Debug = false;
    base::m_Config = false;
    base::m_ConfigPath = "/usr/local/Comtom/conf/service.conf";
}

LinuxEntrance::~LinuxEntrance()
{
}

void LinuxEntrance::init(int argc, char **argv)
{
    //保存程序名称
    ACE_OS::strcpy(m_AppName, argv[0]);

    //参数分析，接受hdc三个参数，c后可接其他内容
    const char options[] = "hdc:";
    ACE_Get_Opt cmd(argc, argv, options,  1, 0, ACE_Get_Opt::PERMUTE_ARGS, 1);

    //TODO:设置长参数总是失败
    cmd.long_option(ACE_TEXT("help"), 'h', ACE_Get_Opt::ARG_REQUIRED);
    cmd.long_option(ACE_TEXT("debug"), 'd', ACE_Get_Opt::ARG_REQUIRED);
    cmd.long_option(ACE_TEXT("config"), 'c', ACE_Get_Opt::ARG_REQUIRED);

    int opt = 0;
    while((opt = cmd()) != EOF)
    {
        switch(opt)
        {
        case 'h':
            m_Help = true;
            break;
        case 'd':
            m_Debug = true;
            break;
        case 'c':
            m_Config = true;
            m_ConfigPath = cmd.opt_arg();
            if (m_ConfigPath.empty())
            {
                m_Help = true;
            }
            break;
        default:
            m_Help = true;
            break;
        }
    }
}


int LinuxEntrance::entry()
{
    if (m_Help)
    {
        this->printUsage();
        return 0;
    }
     
    //初始化运行路径、配置文件路径等
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
        if (m_Debug)
        {
            m_Deamon = IDaemon::CreateInstance(IDaemon::SRV_Consoles);
        }
        else
        {
            m_Deamon = IDaemon::CreateInstance(IDaemon::SRV_Service);
        }

        if (m_Deamon == NULL)
        {
            throw Exception("Failed to create IDaemon object and IDaemon object is NULL");
        }
        
        m_Deamon->Start();
        return 0;
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

void LinuxEntrance::printUsage()
{
    cout << "Usage: " << APP_NAME << " [options]" << endl
        << "Run IPBC service with options" << endl
        << "\t-d:\t\t\tRun servece with debug mode;" << endl
        << "\t-c <ConfigFile>:\tSpecified config file;" << endl
        << "\t-h:\t\t\tShow the help info and exit." << endl;
}

void LinuxEntrance::initPath()
{
    char workPath[256]; 
    //设置当前工作路径
    ACE_OS::strcpy(workPath, getenv("_"));
    if (workPath != NULL && ACE_OS::strstr(workPath, m_AppName) != NULL)
    {
        char *temp = ACE_OS::strrchr(workPath, '/');    
        *temp = '\0';
        ACE_OS::chdir(workPath);
    }
    else
    {
        throw Exception("Failed to init working path of service");
    }

    //设置配置文件路径,默认配置文件路径为工作路径的相对路径../conf/IPBCService.conf
    if (m_Config == false)
    {
        ACE_OS::strcpy(workPath, getcwd(NULL, 0));  
        char *tmp = ACE_OS::strrchr(workPath, '/');
        *tmp = '\0';
        char confPath[MAX_PATH] = {0};
        ACE_OS::snprintf(confPath, MAX_PATH, "%s/conf/%s.conf", workPath, APP_NAME);
        m_ConfigPath = confPath;
    }
}

void LinuxEntrance::initConfig()
{
    SVR_CONF::instance()->init(m_ConfigPath);    
}

void LinuxEntrance::initLog()
{
    LevelsMask lv = LEV_INFO|LEV_ERROR;
    if (SVR_CONF::instance()->getLogInfo()->Debug)
    {
        lv = lv | LEV_DEBUG;
    }
    
    if (m_Debug)
    {
        EngineMaker::MakeConsoleEngine(lv);
    }
    
    std::string logPath = SVR_CONF::instance()->getLogInfo()->Path;
    if (logPath.empty())
    {
        char workPath[260]={0};
        ACE_OS::strcpy(workPath, getcwd(NULL, 0));    
        char *tmp = ACE_OS::strrchr(workPath, '/');
        *tmp = '\0';
        char tmpLogPath[MAX_PATH] = {0};
        ACE_OS::snprintf(tmpLogPath, MAX_PATH, "%s/log/%s.log", workPath, APP_NAME);
        logPath = tmpLogPath;
    }
    
    EngineMaker::MakeFileEngine(logPath, 
        SVR_CONF::instance()->getLogInfo()->Size, 
        SVR_CONF::instance()->getLogInfo()->Backup, lv);

}

void LinuxEntrance::exit()
{
    m_Deamon->Stop();
}


#endif  //WIN32


