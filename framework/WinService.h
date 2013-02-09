/**
* WinService define that inherit from IDaemon interface
*
* Implements IDaemon interface for windows platform
*
* @project: ipbc_2Muse
* @file : WinService.h
* @date : 2011-11-10
* @author : Robin.L
*
*/


#if !defined(_IPBC_2MUSE_WINSERVICE_H_)
#define _IPBC_2MUSE_WINSERVICE_H_

#ifdef WIN32

//////////////////////////////////////////////////////////////////////////
#include <ace/NT_Service.h>
#include <ace/Mutex.h>


//////////////////////////////////////////////////////////////////////////
/**
* Windows服务接口类，继承自IDaemon接口。\n
* 提供对Windows服务的安装，卸载，运行，终止等操作。
*/
class WinService : public ACE_NT_Service
{
	typedef ACE_NT_Service base;

public:
	WinService();
	~WinService();
	virtual void Start();
	virtual void Stop();
	virtual void Setup();
	virtual void Remove();
	virtual void Run();

private:
	virtual int svc(void);
	virtual void handle_control (DWORD control_code);

private:
	bool m_ThreadSign;
};

typedef ACE_Singleton<WinService, ACE_Mutex> SERVICE;

#endif	//WIN32

#endif  //_IPBC_2MUSE_WINSERVICE_H_
