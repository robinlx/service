// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#ifndef _POP_LIB_SERVICE_STDAFX_H_
#define _POP_LIB_SERVICE_STDAFX_H_


#ifdef WIN32
    #include "targetver.h"
    #include <stdio.h>
    #include <tchar.h>
#endif // WIN32

// TODO: 在此处引用程序需要的其他头文件
#include <ace/OS.h>

#include "logger/Logger.h"
#include "common/Exception.h"

//////////////////////////////////////////////
//TODO:编码时使用
#include <iostream>
using std::cout;
using std::endl;



#endif  //_POP_LIB_SERVICE_STDAFX_H_

