

//
//
//
//  @ Project : Log
//  @ File Name : LogService.cpp
//  @ Date : 2012/12/29
//  @ Author : Robin.L
//	@ Version : 1.0.0.0
//


#include "LogService.h"

LogService::LogService( void )
{

}

LogService::~LogService( void )
{

	EngineListType::iterator iter;
	LogEngine *engine;
	for(iter = m_EngineList.begin(); iter != m_EngineList.end(); )
	{
		engine = *iter;
		iter = m_EngineList.erase(iter);
		delete engine;
	}
}

void LogService::InsertEngine( LogEngine* engine )
{
	EngineListType::iterator iter;
	for(iter = m_EngineList.begin(); iter != m_EngineList.end(); ++iter)
	{
		if ((*iter) == engine)
		{
			return;
		}
	}
	
	m_EngineList.push_back(engine);
}

void LogService::RemoveEngine( const LogEngine* engine )
{
	EngineListType::iterator iter;
	for(iter = m_EngineList.begin(); iter != m_EngineList.end(); ++iter)
	{
		if ((*iter) == engine)
		{
			iter = m_EngineList.erase(iter);;
		}
	}
}

void LogService::Write( const LogMsg& msg )
{
	EngineListType::iterator iter;
	for(iter = m_EngineList.begin(); iter != m_EngineList.end(); ++iter)
	{
		(*iter)->WriteLog(msg);
	}
}


