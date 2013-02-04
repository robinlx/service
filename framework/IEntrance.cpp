//////////////////////////////////////
//File: IEntrance.cpp
//Author:   Robin.L
//Date:     2013.1.31
//Description:
//  服务入口类程序，用于分析程序参数，基本初始化等工作
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



