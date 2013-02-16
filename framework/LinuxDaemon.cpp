/**
* Description
*
* Detail
*
* @project: ipbc_2Muse
* @file : LinuxDaemon.cpp
* @date : 2011-11-10
* @author : Robin.L
*
*/

#include "stdafx.h"
#include "LinuxDaemon.h"

#ifndef WIN32


LinuxDaemon::LinuxDaemon()
{
    m_ThreadSign = false;
}

void LinuxDaemon::Start()
{
    this->initService();

    stringstream stream;
    stream << "Run " << APP_NAME << " with console.";
    Logger::Info(stream.str());

    this->openModuleMgr();

    stream.str("");
    stream << "Stop " << APP_NAME;
    Logger::Info(stream.str());
}

void LinuxDaemon::Stop()
{
    m_ThreadSign = false;
}

/*
void LinuxDaemon::loadModule()
{
	m_ModMgr= IModuleMgr::CreateInstance();
	if (m_ModMgr == NULL)
	{
		Logger::Error("IServiceMgr object is NULL.");
		return;
	}

	try
	{
		if (m_ModMgr)
		{
			m_ModMgr->Init();
			m_ModMgr->Open();
		}
		m_ThreadSign = true;
		while (m_ThreadSign)
		{
			ACE_Time_Value timeout(0, 500*1000);
			ACE_Reactor::instance()->handle_events(timeout); 
		}
	}
	catch (const Exception& ex)
	{
		Logger::Error(ex.message().c_str());
	}

	Logger::Debug("Stop Service process.");
	m_ModMgr->Close();
	delete m_ModMgr;
	m_ModMgr = NULL;
    
}
}*/

void LinuxDaemon::initService()
{
    int pid = fork();
    //父进程退出
    if (pid != 0)
    {
        exit(0);
    }
    else if (pid < 0)
    {
        throw Exception("Failed to create subprocess");
    }

    //子进程继续运行
    //创建新的会话组，子进程成为组长，并与控制终端分离
    setsid();

    /* 调试时不关闭
    for(int i = 0; i < NOFILE; i++) // 关闭打开的文件描述符
    {
        close(i);
    }
    */
    
    umask(0);

    //TODO:网上抄的，具体效果不明确，先留着
    /*
    //防止子进程获取控制终端
    pid = fork();
    //子进程退出
    if (pid != 0)
    {
        exit(0);
    }
    else if (pid < 0)
    {
        throw Exception("Failed to create subprocess");
    }
    */
}

#endif  //WIN32
