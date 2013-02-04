
#include "ConsoleLog.h"
#include <iostream>
#include <time.h>

ConsoleLog::ConsoleLog( LevelsMask lvMask /*= LEV_ALL*/ )
	:LogEngine(lvMask)
{
	m_Type = ENG_CONSOLE;
}

void ConsoleLog::WriteLog( const LogMsg& msg )
{
	//检查日志类型与级别
	if (!(msg.Engines & ENG_CONSOLE) || !(msg.Levels & m_LogLevels))
	{
		return;
	}

	//输出到控制台
	std::cout << msg.LogStr();
}
