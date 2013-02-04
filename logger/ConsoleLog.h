//
//
//
//  @ Project : Log
//  @ File Name : ConsoleLog.h
//  @ Date : 2012/5/4
//  @ Author : 
//
//


#if !defined(_POP_MYLIB_CONSOLELOG_H_)
#define _POP_MYLIB_CONSOLELOG_H_

#include "LogEngine.h"

class ConsoleLog : public LogEngine
{
	typedef LogEngine base;
public:
	ConsoleLog(LevelsMask lvMask = LEV_ALL);

	virtual void WriteLog(const LogMsg& msg);

	virtual bool operator==(const LogEngine& obj) const
	{
		return base::m_Type == obj.Type();
	}
};

#endif  //_CONSOLELOG_H
