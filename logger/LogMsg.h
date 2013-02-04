
#ifndef _POP_MYLIB_LOGMSG_H_
#define _POP_MYLIB_LOGMSG_H_

#include <ace/OS.h>
#include <time.h>
#include <string>
#include <sstream>
#include "Logger.h"



const char LevStrTable[8][16] = { "[None] ", "[Info] ", "[Debug]", "", "[Error]" };

struct LogMsg
{
	time_t Time;
	std::string Msg;
	LevelsMask Levels;
	EnginesMask Engines;

	LogMsg()
		:Msg(""), Levels(0), Engines(ENG_ALL)
	{
		Time = time(NULL);
	}

	LogMsg(const std::string& msg, LevelsMask levs,  EnginesMask engs = ENG_ALL)
		:Msg(msg), Levels(levs), Engines(engs)
	{
		Time = time(NULL);
	}

	
	std::string LogStr() const
	{
		char sztime[32];
		ACE_OS::strftime(sztime, 32, "%m-%d %H:%M:%S", ACE_OS::localtime(&Time));
		std::stringstream stream;
		stream << sztime << " " << LevStrTable[Levels] << " " << Msg << std::endl;
		return stream.str();
	}

	
};



#endif	//_POP_MYLIB_LOGMSG_H_

