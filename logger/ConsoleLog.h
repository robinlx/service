//
//
//
//  @ Project : Logger
//  @ File Name : ConsoleLog.h
//  @ Date : 2012/5/4
//  @ Author : Robin.L
//  @ Description:
//  ����̨��־�ඨ��
//


#if !defined(_POP_MYLIB_CONSOLELOG_H_)
#define _POP_MYLIB_CONSOLELOG_H_

#include "LogEngine.h"

//����̨��־���棬�̳���LogEngin
//���ڽ���־���������̨
class ConsoleLog : public LogEngine
{
	typedef LogEngine base;
public:
    //���캯��
    //lvMask: ָ����־������𣬿�����һ������������𣬲μ�LevelsMask
	ConsoleLog(LevelsMask lvMask = LEV_ALL);

    //д��־
    //msg����־��Ϣ
	virtual void WriteLog(const LogMsg& msg);

    //���������أ�ͨ����־���������ж��Ƿ�����ͬ������
	virtual bool operator==(const LogEngine& obj) const
	{
		return base::m_Type == obj.Type();
	}
};

#endif  //_CONSOLELOG_H
