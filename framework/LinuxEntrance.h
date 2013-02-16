//////////////////////////////////////
//File: LinuxEntrance.h
//Author:   Robin.L
//Date:     2013.1.25
//Description:
//  ���������������ڷ������������������ʼ���ȹ���
/////////////////////////////////////

#ifndef _POP_LIB_SERVICE_LINUXENTRANCE_H_
#define _POP_LIB_SERVICE_LINUXENTRANCE_H_


#include "IEntrance.h"

class IDaemon;


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
    void exit();

private:
    virtual void printUsage();
    void serviceInit();

    void initPath();
    void initConfig();
    void initLog();
protected:
    IDaemon *m_Deamon;
};

#endif // _POP_LIB_SERVICE_LINUXENTRANCE_H_
