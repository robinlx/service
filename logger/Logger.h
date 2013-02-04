//
//
//
//  @ Project : Log
//  @ File Name : Logger.h
//  @ Date : 2012/5/4
//  @ Author : Robin.L
//	@ Version : 1.0.0.0
//
//


#if !defined(_POP_MYLIB_LOGGER_H_)
#define _POP_MYLIB_LOGGER_H_

#include <string>

enum LOG_LEVELS {LEV_ALL = 31, LEV_INFO = 1, LEV_DEBUG = 2, LEV_ERROR = 4};
enum LOG_ENGINES {ENG_ALL = 31, ENG_CONSOLE = 1, ENG_FILE = 2, ENG_DATABASE = 4};

typedef int LevelsMask;
typedef int EnginesMask;
typedef int EngineType;


#ifdef WIN32
#ifdef LOG_EXPORT
#define LOGAPI __declspec(dllexport)
#else
#define LOGAPI __declspec(dllimport)
#endif // LOG_EXPORT
#else	//WIN32
#define LOGAPI
#endif	//WIN#@


/*!
* @ Brief 日志接口
*
*/
class LOGAPI Logger
{	
public:
	/*!
	* @ Brief 
	*
	*/
	static void Info(std::string msg, EnginesMask logEngine = ENG_ALL);
    static void Debug(std::string msg, EnginesMask logEngine = ENG_ALL);
    static void Error(std::string msg, EnginesMask logEngine = ENG_ALL);
};

#endif  //_POP_MYLIB_LOGGER_H_
