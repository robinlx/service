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

LinuxDaemon::LinuxDaemon()
{
    m_ThreadSign = false;
}

void LinuxDaemon::run()
{
    this->initService();

    this->loadModule();
    
    int i = 0;
    while (i++ < 100)
    {
        char buf[255];
        sprintf(buf, "log index %d", i);
        Logger::Info(buf);
        sleep(1);
    }
}

void LinuxDaemon::loadModule()
{/*
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
    */
}

void LinuxDaemon::initService()
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
}

