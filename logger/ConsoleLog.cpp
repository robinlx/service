
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
	//�����־�����뼶��
	if (!(msg.Engines & ENG_CONSOLE) || !(msg.Levels & m_LogLevels))
	{
		return;
	}

	//���������̨
	std::cout << msg.LogStr();
}
