//
//
//
//  @ Project : Log
//  @ File Name : EngineMaker.h
//  @ Date : 2012/12/29
//  @ Author : Robin.L
//	@ Version : 1.0.0.0
//  @ Description
//  日志引擎生成器
//


#if !defined(_COMTOM_V3_COMMON_ENGINEMAKER_H_)
#define _COMTOM_V3_COMMON_ENGINEMAKER_H_

#include "Logger.h"
#include <string>

//日志引擎生成器类，用于生成日志引擎
class LOGAPI EngineMaker
{
public:
	static bool MakeConsoleEngine(LevelsMask lvMask = LEV_ALL);
	static bool MakeFileEngine(const std::string fileName, int fileSize, int backCount, LevelsMask lvMask  = LEV_ALL);
	//static bool MakeDatabaseEngine();
};



#endif  //_COMTOM_V3_COMMON_ENGINEMAKER_H_
