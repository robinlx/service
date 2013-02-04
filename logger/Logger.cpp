//
//
//
//  @ Project : Log
//  @ File Name : Logger.cpp
//  @ Date : 2012/5/4
//  @ Author : 
//
//

#define LOG_EXPORT
#include "Logger.h"
#include <time.h>
#include "LogMsg.h"
#include "LogService.h"


void Logger::Info( std::string msg, int logEngine /*= ENG_ALL*/ )
{
	LogMsg log(msg, LEV_INFO, logEngine);
	LOGSERVICE::instance()->Write(log);

}

void Logger::Debug( std::string msg, int logEngine /*= ENG_ALL*/ )
{
	LogMsg log(msg, LEV_DEBUG, logEngine);
	LOGSERVICE::instance()->Write(log);
}

void Logger::Error( std::string msg, int logEngine /*= ENG_ALL*/ )
{
	LogMsg log(msg, LEV_ERROR, logEngine);
	LOGSERVICE::instance()->Write(log);
}
