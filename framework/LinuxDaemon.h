/**
* Description
*
* Detail
*
* @project: ipbc_2Muse
* @file : LinuxDaemon.h
* @date : 2011-11-10
* @author : Robin.L
*
*/


#if !defined(_LINUXDAEMON_H)
#define _LINUXDAEMON_H


class LinuxDaemon 
{
public:
    LinuxDaemon();
	void run();

private:
    void loadModule();
    void initService();
private:
	volatile bool m_ThreadSign;
};

#endif  //_LINUXDAEMON_H


