//
//
//
//  @ Project : Log
//  @ File Name : EngineMaker.h
//  @ Date : 2012/12/29
//  @ Author : Robin.L
//	@ Version : 1.0.0.0
//
//


#if !defined(_COMTOM_V3_COMMON_ENGINEMAKER_H_)
#define _COMTOM_V3_COMMON_ENGINEMAKER_H_

#include "Logger.h"
#include <string>

class LOGAPI EngineMaker
{
public:
	static bool MakeConsoleEngine(LevelsMask lvMask = LEV_ALL);
	static bool MakeFileEngine(const std::string fileName, int fileSize, int backCount, LevelsMask lvMask  = LEV_ALL);
	//static bool MakeDatabaseEngine();
};



#endif  //_COMTOM_V3_COMMON_ENGINEMAKER_H_
