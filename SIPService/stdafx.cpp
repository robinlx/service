// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// SIPService.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

// TODO: �� STDAFX.H ��
// �����κ�����ĸ���ͷ�ļ����������ڴ��ļ�������

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