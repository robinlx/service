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
#include <string.h>
#include <ace/Get_Opt.h>
#include "Config.h"
#include "logger/EngineMaker.h"
#include "LinuxDaemon.h"
#include "Consoles.h"


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
    if (m_Help == true)
    {
        this->printUsage();
        return 1;
    }
     
    this->initPath();           //初始化路径信息
    this->initConfig();         //初始化配置文件
    this->initLog();
    if (m_Debug == true)
    {
        cout << "Run with debug" << endl;
        Consoles cmd;
        cmd.run();
    }
    else
    {
        cout << "Run as service" << endl;
        LinuxDaemon daemon;
        daemon.run();
    }
    return 0;
}

void LinuxEntrance::printUsage()
{
    cout << "Usage: IPBCService [options]" << endl
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
    cout << "getenv: " << workPath << endl;
    if (workPath != NULL && ACE_OS::strstr(workPath, m_AppName) != NULL)
    {
        char *temp = ACE_OS::strrchr(workPath, '/');    
        *temp = '\0';
        cout << "chdir: " << workPath << endl;
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
        m_ConfigPath = workPath;
        cout << m_ConfigPath << endl;
        m_ConfigPath += "/conf/IPBCService.conf";
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
        logPath = workPath;
        logPath += "/log/IPBCService.log";
    }
    
    EngineMaker::MakeFileEngine(logPath, 
        SVR_CONF::instance()->getLogInfo()->Size, 
        SVR_CONF::instance()->getLogInfo()->Backup, lv);

}
#endif  //WIN32


