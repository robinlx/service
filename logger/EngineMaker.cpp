// 
// 
// 
//  @ Project : Log 
//  @ File Name : EngineMaker.cpp 
//  @ Date : 2012/12/29 
//  @ Author : Robin.L 
// 
// 
 

#include "stdafx.h"
#include "EngineMaker.h" 
#include "LogEngine.h" 
#include "LogService.h" 
#include "ConsoleLog.h" 
#include "FileLog.h" 
 
 
 
bool EngineMaker::MakeConsoleEngine(LevelsMask lvMask) 
{ 
	LogEngine* engine = new ConsoleLog(lvMask); 
	if (engine == NULL) 
	{ 
		return false; 
	} 
	LOGSERVICE::instance()->InsertEngine(engine); 
	return true; 
} 
 
bool EngineMaker::MakeFileEngine( const std::string fileName, int fileSize, int backCount, LevelsMask lvMask /*= LEV_ALL*/ ) 
{ 
	LogEngine* engine = new FileLog(fileName, fileSize, backCount, lvMask);	 
	if (engine == NULL) 
	{ 
		return false; 
	} 
	LOGSERVICE::instance()->InsertEngine(engine); 
	return true; 
} 
 
 

