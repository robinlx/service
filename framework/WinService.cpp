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

ACE_NT_SERVICE_DEFINE (APP_NAME,
					   WinService,
					   ACE_TEXT (APP_NAME));

WinService::WinService()
{
	ACE::init ();
	this->name(ACE_TEXT (APP_NAME), ACE_TEXT (APP_NAME));
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
		throw Exception(buf);
	}

	Logger::Info("Start service successful.");
}

void WinService::Stop()
{
	if (base::stop_svc() != 0)
	{
		char buf[1024];
		ACE_OS::sprintf(buf, "Failed stop service: %d, %s", GetLastError(), ACE_OS::dlerror());
		throw Exception(buf);
	}
}

void WinService::Setup()
{
	char exec_path[512] = {0};
	int len = GetModuleFileName(NULL, exec_path, sizeof(exec_path)); 
	if (0 == len)
	{
		char buf[1024];
		ACE_OS::sprintf(buf, "Failed to get module path: %d, %s", GetLastError(), ACE_OS::dlerror());
		throw Exception(buf);
	}

    ACE_OS::strcat(exec_path, " -x");
	if (base::insert(SERVICE_AUTO_START, SERVICE_ERROR_IGNORE, exec_path) != 0)
	{
		char buf[1024];
		ACE_OS::sprintf(buf, "Failed to insert service: %d, %s", GetLastError(), ACE_OS::dlerror());
		throw Exception(buf);
	}

	Logger::Info("Setup service successful.");
}

void WinService::Remove()
{
	if (base::remove() != 0)
	{
		char buf[1024];
		ACE_OS::sprintf(buf, "Failed remove service: %d, %s", GetLastError(), ACE_OS::dlerror());
		throw Exception(buf);
	}

	Logger::Info("Remove service successful.");
	
}

int WinService::svc(void)
{
	base::report_status(SERVICE_RUNNING);

    this->openModuleMgr();

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
	ACE_NT_SERVICE_RUN (APP_NAME, SERVICE::instance(), ret);
	if (ret == 0)	//Failed to call
	{
		char buf[1024];
		ACE_OS::sprintf(buf, "Failed to call service: %d, %s", 
            GetLastError(), ACE_OS::dlerror());
		throw Exception(buf);
	}
}


#endif // WIN32
