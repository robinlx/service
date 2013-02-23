//
//
//
//  @ Project : Log
//  @ File Name : DatabaseLog.h
//  @ Date : 2012/5/4
//  @ Author : Robin.L
//  @ Description:
//  数据库日志引擎


#if !defined(_DATABASELOG_H)
#define _DATABASELOG_H

#include "LogEngine.h"

//数据库日志引擎，继承自LogEngin
//用于将日志输出到数据库
//TODO：暂时未实现
class DatabaseLog : public LogEngine
{
};

#endif  //_DATABASELOG_H
