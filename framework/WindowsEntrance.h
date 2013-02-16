//////////////////////////////////////
//File: WindowsEntrance.h
//Author:   Robin.L
//Date:     2013.2.6
//Description:
//  windows服务入口类程序，用于分析程序参数，基本初始化等工作
/////////////////////////////////////

#ifndef _POP_LIB_SERVICE_WINDOWSENTRANCE_H_
#define _POP_LIB_SERVICE_WINDOWSENTRANCE_H_

#include "IEntrance.h"

class IDaemon;

class WindowsEntrance :
    public IEntrance
{
public:
    WindowsEntrance(void);
    ~WindowsEntrance(void);

public:
    virtual void init(int argc, char **argv);
    virtual int entry();
    virtual void exit();

private:
    virtual void printUsage();

    void initPath();
    void initConfig();
    void initLog();

private:
    bool m_Insert;
    bool m_Remove;
    bool m_Start;
    bool m_Kill;
    bool m_Run;

    IDaemon *m_Deamon;
};

#endif  //_POP_LIB_SERVICE_WINDOWSENTRANCE_H_