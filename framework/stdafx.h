// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#ifndef _POP_LIB_SERVICE_STDAFX_H_
#define _POP_LIB_SERVICE_STDAFX_H_


#ifdef WIN32
    #include "targetver.h"
    #include <stdio.h>
    #include <tchar.h>
#endif // WIN32

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include <ace/OS.h>

#include "Config.h"
#include "logger/Logger.h"
#include "common/Exception.h"

#include <sstream>

//////////////////////////////////////////////
const char APP_NAME[] = "IPBCService";
const char APP_VERSION[] = "3.1.0";

//////////////////////////////////////////////
//TODO:����ʱʹ��
#include <iostream>
using std::cout;
using std::endl;



#endif  //_POP_LIB_SERVICE_STDAFX_H_

