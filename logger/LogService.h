//
//
//
//  @ Project : Log
//  @ File Name : LogService.h
//  @ Date : 2012/12/29
//  @ Author : Robin.L
//	@ Version : 1.0.0.0
//

#ifndef _COMTOM_V3_COMMON_LOGSERVICE_H_
#define _COMTOM_V3_COMMON_LOGSERVICE_H_

#include <ace/Synch.h>
#include <ace/Singleton.h>
#include <vector>

#include "LogEngine.h"

class LogService
{
public:
	LogService(void);
	~LogService(void);

	void InsertEngine(LogEngine* engine);
	void RemoveEngine(const LogEngine* engine);

	void Write(const LogMsg& msg);

protected:
	typedef std::vector<LogEngine*> EngineListType;
	EngineListType m_EngineList;
};

//typedef ACE_Singleton<LogService, ACE_Mutex> LOGSERVICE;
extern LogService g_Service;

#endif	//_COMTOM_V3_COMMON_LOGSERVICE_H_

