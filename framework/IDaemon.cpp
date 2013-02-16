
#include "stdafx.h"
#include "IDaemon.h"

#include <ace/Reactor.h>

#include "WinService.h"
#include "LinuxDaemon.h"
#include "Consoles.h"
#include "IModuleMgr.h"



IDaemon* IDaemon::CreateInstance( SRV_TYPE svrType )
{
	IDaemon *pSrv = NULL;
	if (svrType == SRV_Service)
	{
#ifdef WIN32
		pSrv = SERVICE::instance();
#else
		pSrv = new LinuxDaemon;
#endif	//WIN32
	}
	else
	{
		pSrv = new Consoles;
	}
	
	return pSrv;
}


void IDaemon::DestoryInstance( IDaemon*& pSrv )
{
	//TODO:��Ҫ���ݲ�ͬƽ̨��IDaemonָ������ͷ�
	//ĿǰWinServiceʹ�õ���ģʽ����ACE��������Ҫ�ͷ�
	//�������������඼��ʵ���ٿ�����ͷ�
}

IDaemon::IDaemon()
{
	m_ModMgr = NULL;
}

void IDaemon::Start()
{
	throw Exception("Start function isn't implemented.");
}

void IDaemon::Stop()
{
	throw Exception("Stop function isn't implemented.");
}

void IDaemon::Setup()
{
	throw Exception("Setup function isn't implemented.");
}

void IDaemon::Remove()
{
	throw Exception("Remove function isn't implemented.");
}

void IDaemon::Run()
{
	throw Exception("Run function isn't implemented.");
}

void IDaemon::openModuleMgr()
{
    m_ModMgr = IModuleMgr::CreateInstance();
    if (m_ModMgr == NULL)
    {
        stringstream stream;
        stream << "Failed create IModuleMgr and IModuleMgr object is NULL.";
        throw Exception(stream.str());
    }

    //��ʼ��ModuleList
    m_ModMgr->Init();

    //��������ģ��
    m_ModMgr->Open();

    //ѭ������߳̽�����־
    m_ThreadSign = true;
    while (m_ThreadSign)
    {
        ACE_Time_Value timeout(0, 500*1000);
        ACE_Reactor::instance()->handle_events(timeout); 
    }
 
    //ж�ظ���ģ��
    m_ModMgr->Close();

    IModuleMgr::DestoryInstance(m_ModMgr);
}
