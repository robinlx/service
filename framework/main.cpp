
#include "stdafx.h"
#include "IEntrance.h"
#include <ace/ACE.h>

IEntrance *g_Entrance = NULL;


//�źŴ�����������SIGINT�ж�
void signHandle(int sign)
{
    //����SIGINT�ж�ʱֹͣ����
    if (sign == SIGINT && g_Entrance != NULL)
    {
        g_Entrance->exit();
    }
    
}

    
int main(int argc, char **argv)
{
    ACE::init();
    //����SIGINT��Ӧ������
    signal(SIGINT,signHandle); 

    g_Entrance = IEntrance::CreateInstance();
    g_Entrance->init(argc, argv);
    int res = g_Entrance->entry();

    ACE::fini();
    return res;
}

