//////////////////////////////////////
//File: IEntrance.h
//Author:   Robin.L
//Date:     2013.1.25
//Description:
//  ���������������ڷ������������������ʼ���ȹ���
/////////////////////////////////////

#ifndef _POP_LIB_SERVICE_IENTRANCE_H_
#define _POP_LIB_SERVICE_IENTRANCE_H_

#include <string>

class IEntrance;

IEntrance* CreateEntranceInstance();


class IEntrance
{
protected:
    IEntrance() {};
    ~IEntrance() {};

public:
    virtual void init(int argc, char **argv) = 0;
    virtual int entry() = 0;

private:
    virtual void printUsage() = 0;
    
protected:
    bool m_Help;
    bool m_Debug;
    bool m_Config;

    std::string m_ConfigPath;
};

#endif //_POP_LIB_SERVICE_IENTRANCE_H_

