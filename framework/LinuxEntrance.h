//////////////////////////////////////
//File: LinuxEntrance.h
//Author:   Robin.L
//Date:     2013.1.25
//Description:
//  服务入口类程序，用于分析程序参数，基本初始化等工作
/////////////////////////////////////

#ifndef _POP_LIB_SERVICE_LINUXENTRANCE_H_
#define _POP_LIB_SERVICE_LINUXENTRANCE_H_

#include "IEntrance.h"

class LinuxEntrance
    :public IEntrance
{
    typedef IEntrance base;
public:
    LinuxEntrance();
    ~LinuxEntrance();

public:
    void init(int argc, char **argv);
    int entry();

private:
    virtual void printUsage();
    void serviceInit();
    void run();

    void initPath();
    void initConfig();

protected:
    char m_AppName[255];
};

#endif // _POP_LIB_SERVICE_LINUXENTRANCE_H_
