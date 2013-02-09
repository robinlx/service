//
//
//
//  @ Project : Log
//  @ File Name : LogEngine.h
//  @ Date : 2012/5/4
//  @ Author : Robin.L
//	@ Version : 1.0.0.0
//


#if !defined(_POP_MYLIB_LOGENGINE_H_)
#define _POP_MYLIB_LOGENGINE_H_

#include "Logger.h"
#include "LogMsg.h"

class LogEngine
{
public:
	LogEngine(LevelsMask lvMask):m_LogLevels(lvMask) {};
    virtual ~LogEngine() {};
	
    virtual void WriteLog(const LogMsg& msg) = 0;

	EngineType Type() const
	{
		return m_Type;
	}
  
	virtual bool operator==(const LogEngine& obj) const
	{
		return true;
	}

protected:
	LevelsMask m_LogLevels;
	EngineType m_Type;
};

#endif  //_POP_MYLIB_LOGENGINE_H_
