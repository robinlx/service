/**
* Exception Class define
*
* Defined ExceptionSource class and Exception base class
*
* @project: common
* @file : Exception.h
* @date : 2011-11-14
* @author : Robin.L
* 
* 这个文件中的定义与V3中的Exception定义相同，
* 在实现中使用StringStream代替super_string，
* 以消除对sstring的依赖
*
*/

#if !defined(_IPBC_2MUSE_COMMON_EXCEPTION_H_)
#define _IPBC_2MUSE_COMMON_EXCEPTION_H_

#include <sstream>
using std::stringstream;
#include <errno.h>

#include <ace/OS.h>
#include "Define.h"

#ifdef __GNUC__
/* Version 2.4 and later of GCC define a magical variable `__PRETTY_FUNCTION__'
which contains the name of the function currently being defined.
This is broken in G++ before version 2.6.
C9x has a similar variable called __func__, but prefer the GCC one since
it demangles C++ function names.  */
# if defined __cplusplus ? __GNUC_PREREQ (2, 6) : __GNUC_PREREQ (2, 4)
#   define __FUNCTION	__func__ //__PRETTY_FUNCTION__
# else
#  if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
#   define __FUNCTION	__func__
#  else
#   define __FUNCTION	((__const char *) 0)
#  endif
# endif
#else
#define __FUNCTION __FUNCTION__
#endif


struct ExceptionSource
{
	std::string _func;
	std::string _file;
	int _line;

	ExceptionSource(const char* func, const char* file, int line) :
	_func((func)?(func):"unknown"), _file((file)?(file):"unknown"), _line(line)
	{
		//Load file name from file path
		file = strrchr(file, PATH_SEPARATOR);
		if (file != NULL)
			_file = file + 1;
	}

	ExceptionSource() : _func("unknown"), _file("unknown"), _line(0)
	{}
};

#define CURRENT_SOURCE ExceptionSource(__FUNCTION, __FILE__, __LINE__)
inline ExceptionSource currentSource()
{
    return ExceptionSource(__FUNCTION, __FILE__, __LINE__);
}

class Exception
{
public:
	Exception() : _source(CURRENT_SOURCE)
	{}

	Exception(const char* szMessage, const ExceptionSource& src = ExceptionSource()) :
	_message(szMessage), _source(src)
	{}

	Exception(const std::string& msg, const ExceptionSource& src = ExceptionSource()) :
	_message(msg), _source(src)
	{}

	Exception(const ExceptionSource& src) : _source(src)
	{}

	virtual ~Exception()
	{}

	virtual std::string message()const 
	{
		return _message;
	}

	virtual std::string tostr()const 
	{
		stringstream stream;
		stream << _message << "source=[" << _source._file << ":" << _source._line << "]";
		return  stream.str();
	}

	const ExceptionSource& source()const {
		return _source;
	}

protected:
	std::string _message;

private:
	ExceptionSource _source;
};

class OsException : public Exception
{
public:
    OsException(const std::string &msg, const ExceptionSource& src = ExceptionSource()) 
    : Exception(src), errCode(errno)
    {
		stringstream stream;
		stream << "[" << errCode << ":" << ACE_OS::strerror(errCode) << "]";
		_message = msg + stream.str();
    }
    
    int errCode;
};


template <typename exception_tag>
class DerivedException: public Exception, private exception_tag
{
public:
    DerivedException(const char* szMessage, const ExceptionSource& src = CURRENT_SOURCE) 
    : Exception(szMessage, src)
    {}
    
    DerivedException(const std::string& msg, const ExceptionSource& src = currentSource()) 
    : Exception(msg, src)
    {}
};


#define DEFINE_EXCEPTION(exception_t) \
struct tag_##exception_t{};  \
typedef DerivedException<tag_##exception_t> exception_t;


#define EXCEPTION(m) Exception((m), CURRENT_SOURCE)
#define OS_EXCEPTION(m) OsException(m, CURRENT_SOURCE)

#endif	//_IPBC_2MUSE_COMMON_EXCEPTION_H_
