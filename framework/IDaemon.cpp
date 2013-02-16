
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
	//TODO:需要根据不同平台对IDaemon指针进行释放
	//目前WinService使用单例模式，由ACE管理，不需要释放
	//等其他两个子类都现实后再看如何释放
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

    //初始化ModuleList
    m_ModMgr->Init();

    //启动各个模块
    m_ModMgr->Open();

    //循环检测线程结束标志
    m_ThreadSign = true;
    while (m_ThreadSign)
    {
        ACE_Time_Value timeout(0, 500*1000);
        ACE_Reactor::instance()->handle_events(timeout); 
    }
 
    //卸载各个模块
    m_ModMgr->Close();

    IModuleMgr::DestoryInstance(m_ModMgr);
}
