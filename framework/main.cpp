
#include "stdafx.h"
#include "IEntrance.h"
#include <ace/ACE.h>

IEntrance *g_Entrance = NULL;


//信号处理函数，处理SIGINT中断
void signHandle(int sign)
{
    //捕获SIGINT中断时停止服务
    if (sign == SIGINT && g_Entrance != NULL)
    {
        g_Entrance->exit();
    }
    
}

    
int main(int argc, char **argv)
{
    ACE::init();
    //设置SIGINT对应处理函数
    signal(SIGINT,signHandle); 

    g_Entrance = IEntrance::CreateInstance();
    g_Entrance->init(argc, argv);
    int res = g_Entrance->entry();

    ACE::fini();
    return res;
}

