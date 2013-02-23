//
//
//
//  @ Project : Logger
//  @ File Name : ConsoleLog.h
//  @ Date : 2012/5/4
//  @ Author : Robin.L
//  @ Description:
//  控制台日志类定义
//


#if !defined(_POP_MYLIB_CONSOLELOG_H_)
#define _POP_MYLIB_CONSOLELOG_H_

#include "LogEngine.h"

//控制台日志引擎，继承自LogEngin
//用于将日志输出到控制台
class ConsoleLog : public LogEngine
{
	typedef LogEngine base;
public:
    //构造函数
    //lvMask: 指定日志输出级别，可以是一个或多个输出级别，参见LevelsMask
	ConsoleLog(LevelsMask lvMask = LEV_ALL);

    //写日志
    //msg：日志信息
	virtual void WriteLog(const LogMsg& msg);

    //操作符重载，通过日志引擎类型判断是否是相同的引擎
	virtual bool operator==(const LogEngine& obj) const
	{
		return base::m_Type == obj.Type();
	}
};

#endif  //_CONSOLELOG_H
