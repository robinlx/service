//#include <unistd.h>
#include "stdafx.h"
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "IEntrance.h"

#ifndef NOFILE
#define NOFILE 3
#endif

#include <ace/ACE.h>

#ifdef WIN32
#pragma comment(lib, "aced.lib")
#endif //WIN32

void signHandle(int sign)
{
    cout << "Handle sigint" << endl;
}

void init_daemon()
{
#ifndef WIN32

    int pid;
    int i;
    if(pid = fork()) exit(0); //�����̣��˳�

    else if(pid < 0) exit(1); //forkʧ��

    /* �ӽ��̼���ִ�� */
    setsid(); //�����µĻỰ�飬�ӽ��̳�Ϊ�鳤����������ն˷���

    /* ��ֹ�ӽ��̣��鳤����ȡ�����ն� */
    if(pid = fork()) exit(0); //�����̣��˳�

    else if(pid < 0) exit(1); //fork�����˳�

    /* �ڶ��ӽ��̼���ִ�� , �ڶ��ӽ��̲����ǻ�Ự���鳤*/

    //for(i = 0; i < NOFILE; i++) /* �رմ򿪵��ļ�������*/
    ////{
    ////close(i);
    ////}
    const char *dir = "/tmp";
    int a = chdir(dir); /* �л�����Ŀ¼ */
    umask(0); /* �����ļ��������� */
    return;

#endif //WIN32
}
    
int main(int argc, char **argv)
{
    
    ACE::init();
//    signal(SIGINT,signHandle); 
    IEntrance *entrance = CreateEntranceInstance();
    entrance->init(argc, argv);
    entrance->entry();
    ACE::fini();
    getchar();
    exit(0);
    FILE *fp;
    
    signal(SIGCHLD, SIG_IGN); /* �����ӽ��̽����źţ���ֹ���ֽ�ʬ���� */
    
    init_daemon();
    
    while(1)
    {
        //sleep(1);
        if((fp = fopen("/home/robin/test.log", "a")) != NULL)
        {
            fprintf(fp, "%s\n", "test message");
            fclose(fp);
        }
    }

    return 0;
}

