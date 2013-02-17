// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#ifndef _COMTOM_V3_SIPSERVICE_STDAFX_H_
#define _COMTOM_V3_SIPSERVICE_STDAFX_H_

#ifdef WIN32
    #include "targetver.h"
    #define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
    // Windows 头文件:
    #include <windows.h>
#endif // WIN32



// TODO: 在此处引用程序需要的其他头文件


#include <string>

//TODO:调试输出
#include <iostream>
using std::cout;
using std::endl;
#define OUTPUT(msg) cout<<msg<<endl

#endif //_COMTOM_V3_SIPSERVICE_STDAFX_H_
