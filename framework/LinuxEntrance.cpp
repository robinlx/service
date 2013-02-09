//////////////////////////////////////
//File: LinuxEntrance.cpp
//Author:   Robin.L
//Date:     2013.1.25
//Description:
//  ���������������ڷ������������������ʼ���ȹ���
/////////////////////////////////////



#include "stdafx.h"

#ifndef WIN32
#include "LinuxEntrance.h"
#include <string.h>
#include <ace/Get_Opt.h>
#include "Config.h"


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
    //�����������
    ACE_OS::strcpy(m_AppName, argv[0]);

    //��������������hdc����������c��ɽ���������
    const char options[] = "hdc:";
    ACE_Get_Opt cmd(argc, argv, options,  1, 0, ACE_Get_Opt::PERMUTE_ARGS, 1);

    //TODO:���ó���������ʧ��
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
     
    this->initPath();           //��ʼ��·����Ϣ
    this->initConfig();         //��ʼ�������ļ�

    if (m_Debug == true)
    {
        cout << "Run with debug" << endl;
        this->run();
    }
    else
    {
        cout << "Run as service" << endl;
        this->serviceInit();
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

void LinuxEntrance::serviceInit()
{
    int pid = fork();
    //�������˳�
    if (pid != 0)
    {
        exit(0);
    }
    else if (pid < 0)
    {
        //forkʧ��
        exit(1);
    }

    //�ӽ��̼�������
    //�����µĻỰ�飬�ӽ��̳�Ϊ�鳤����������ն˷���
    setsid();

    /* ����ʱ���ر�
    for(int i = 0; i < NOFILE; i++) // �رմ򿪵��ļ�������
    {
        close(i);
    }
    */
    

//    chdir("/");
    umask(0);

    //TODO:���ϳ��ģ�����Ч������ȷ��������
    /*
    //��ֹ�ӽ��̻�ȡ�����ն�
    pid = fork();
    //�ӽ����˳�
    if (pid != 0)
    {
        exit(0);
    }
    else if (pid < 0)
    {
        //forkʧ��
        exit(1);
    }
    */
    
    this->run();
}


void LinuxEntrance::run()
{
    //TODO:debug output
    //Log config
    cout << "---- Log config info----" << endl
        << "Debug:" << SVR_CONF::instance()->getLogInfo()->Debug << endl
        << "Size: " << SVR_CONF::instance()->getLogInfo()->Size << endl
        << "Backup:" << SVR_CONF::instance()->getLogInfo()->Backup << endl
        << "Path:  " << SVR_CONF::instance()->getLogInfo()->Path << endl;
    
    int i = 0;
    while (i++ < 100)
    {
        cout << "pwd: " << getcwd(NULL,0) << endl;
        sleep(1);
    }
}

void LinuxEntrance::initPath()
{
    char workPath[256]; 
    //���õ�ǰ����·��
    ACE_OS::strcpy(workPath, getenv("_"));
    cout << "getenv: " << workPath << endl;
    if (workPath != NULL && ACE_OS::strstr(workPath, m_AppName) != NULL)
    {
        char *temp = ACE_OS::strrchr(workPath, '/');    
        *temp = '\0';
        cout << "chdir: " << workPath << endl;
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
        m_ConfigPath += "/conf/IPBCService.conf";
    }
}

void LinuxEntrance::initConfig()
{
    try
    {
        SVR_CONF::instance()->init(m_ConfigPath);    
    }
    catch(ConfException &ex)
    {
        cout << "Exception: " <<  ex.message() << endl;
    }
}

#endif  //WIN32