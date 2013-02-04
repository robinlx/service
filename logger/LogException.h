

#ifndef _POP_MYLIB_LOGEXCEPTION_H_
#define  _POP_MYLIB_LOGEXCEPTION_H_

#include "Exception.h"

class LogException
	:public Exception
{
public:
	LogException(const char* szMessage) 
		: Exception(szMessage)
	{}

	LogException(const std::string& msg) 
		: Exception(msg)
	{}
};


#endif