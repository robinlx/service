// stdafx.cpp : 只包括标准包含文件的源文件
// SIPService.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中
// 引用任何所需的附加头文件，而不是在此文件中引用

#ifdef WIN32
    #ifdef _DEBUG
        #pragma comment(lib, "aced.lib")
        #pragma comment(lib, "tinyxmld_STL.lib")
        #pragma comment (lib, "logger_d.lib")
    #else
        #pragma comment(lib, "ace.lib")
        #pragma comment(lib, "tinyxml_STL.lib")
        #pragma comment (lib, "logger.lib")
    #endif // _DEBUG
#endif // WIN32