//////////////////////////////////////
//File: IEntrance.cpp
//Author:   Robin.L
//Date:     2013.1.31
//Description:
//  ���������������ڷ������������������ʼ���ȹ���
/////////////////////////////////////

#include "IEntrance.h"
#include "LinuxEntrance.h"

IEntrance* CreateEntranceInstance()
{
#ifdef WIN32
    return new WindowsEntrance;
#else
    return new LinuxEntrance;
#endif  //WIN32
}



