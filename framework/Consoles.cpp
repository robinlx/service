/**
* Description
*
* Detail
*
* @project: ipbc_2Muse
* @file : Consoles.cpp
* @date : 2011-11-10
* @author : Robin.L
*
*/
#include "stdafx.h"
#include "Consoles.h"
#include <ace/Reactor.h>


Consoles::Consoles()
{
	m_ThreadSign = false;
	//ACE_Reactor::instance()->register_handler(SIGINT, this);
}

void Consoles::run()
{
    /*
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
    int i = 0;
    m_ThreadSign = true;
    while (m_ThreadSign)
		{char buf[255];
            sprintf(buf, "Consoles thread info %d", i++);
            Logger::Info(buf);
			ACE_Time_Value timeout(0, 500*1000);
 			ACE_Reactor::instance()->handle_events(timeout); 
		}
}

int Consoles::handle_signal( int signum, siginfo_t * /* = 0 */, ucontext_t * /* = 0 */ )
{
	if (signum == SIGINT)
	{
		this->m_ThreadSign = false;
	}
	return 0;
}



