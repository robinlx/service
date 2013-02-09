/**
* Description
*
* Detail
*
* @project: ipbc_2Muse
* @file : WinService.cpp
* @date : 2011-11-10
* @author : Robin.L
*
*/

#include "stdafx.h"
#include <ace/Reactor.h>
#include "WinService.h"



#ifdef WIN32

const char *ServerName = "IPBCService";

ACE_NT_SERVICE_DEFINE (ServerName,
					   WinService,
					   ACE_TEXT (ServerName));

WinService::WinService()
{
	ACE::init ();
	this->name(ACE_TEXT (ServerName), ACE_TEXT (ServerName));
	m_ThreadSign = false;
}

WinService::~WinService()
{
	ACE::fini ();
}


void WinService::Start()
{
	if (base::start_svc() != 0)
	{
		char buf[1024];
		ACE_OS::sprintf(buf, "Failed start service: %d, %s", GetLastError(), ACE_OS::dlerror());
		Logger::Error(buf);
	}
	else
	{
		Logger::Info("Start service successful.");
	}
}

void WinService::Stop()
{
	if (base::stop_svc() != 0)
	{
		char buf[1024];
		ACE_OS::sprintf(buf, "Failed stop service: %s", ACE_OS::dlerror());
		Logger::Error(buf);
	}
}

void WinService::Setup()
{
	char exec_path[512] = {0};
	int len = GetModuleFileName(NULL, exec_path, sizeof(exec_path)); 
	if (0 == len)
	{
		char buf[1024];
		ACE_OS::sprintf(buf, "Failed to get module path: %s", ACE_OS::dlerror());
		Logger::Error(buf);
		return;
	}

    ACE_OS::strcat(exec_path, " -x");
	if (base::insert(SERVICE_AUTO_START, SERVICE_ERROR_IGNORE, exec_path) != 0)
	{
		char buf[1024];
		ACE_OS::sprintf(buf, "Failed to insert service: %s", ACE_OS::dlerror());
		Logger::Error(buf);
		return;
	}

	Logger::Info("Setup service successful.");
}

void WinService::Remove()
{
	if (base::remove() != 0)
	{
		char buf[1024];
		ACE_OS::sprintf(buf, "Failed remove service: %s", ACE_OS::dlerror());
		Logger::Error(buf);
	}
	else
	{
		Logger::Info("Remove service successful.");
	}
}

int WinService::svc(void)
{
	base::report_status(SERVICE_RUNNING);
    while (m_ThreadSign)
    {
        ACE_Time_Value timeout(0, 500*1000);
        ACE_OS::sleep(timeout);
        Logger::Info("Service is running.");
    }
    /*
	m_ModMgr= IModuleMgr::CreateInstance();
	if (m_ModMgr == NULL)
	{
		Logger::Error("IServiceMgr object is NULL.");
	}

	try
	{
		if (m_ModMgr)
		{
			m_ModMgr->Init();
			m_ModMgr->Open();
			
			while (m_ThreadSign)
			{
				ACE_Time_Value timeout(0, 500*1000);
				ACE_Reactor::instance()->handle_events(timeout); 
			}
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
	return 0;
}

void WinService::handle_control( DWORD control_code )
{
	if (control_code == SERVICE_CONTROL_SHUTDOWN
		|| control_code == SERVICE_CONTROL_STOP)
	{
		base::report_status (SERVICE_STOP_PENDING);
		m_ThreadSign = false;
	}
	else
		base::handle_control (control_code);
}

void WinService::Run()
{
	m_ThreadSign = true;
	ACE_NT_SERVICE_RUN (ServerName,
		SERVICE::instance(),
		ret);
	if (ret == 0)	//Failed to call
	{
		char buf[1024];
		ACE_OS::sprintf(buf, "Failed to call service: %s,%d", ACE_OS::dlerror(),GetLastError());
		Logger::Error(buf);
	}
}


#endif // WIN32
