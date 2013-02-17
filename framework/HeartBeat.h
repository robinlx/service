#if !defined(_IPBC_2MUSE_HEARTBEAT_H_)
#define _IPBC_2MUSE_HEARTBEAT_H_


#include <ace/Event_Handler.h>
//#include <mysql++.h>


#include "IModule.h"

class HeartBeat
	:public IModule, public ACE_Event_Handler
{
public:
	HeartBeat(void);
	~HeartBeat(void);

    virtual void Init(const std::string& workPath) {};
	virtual void Start();
	virtual void Stop();

private:
	int handle_timeout(const ACE_Time_Value &current_time, const void *act /* = 0 */);
	void UpdateHeartBeat();

private:
//	mysqlpp::Connection m_Conn;
};




#endif	//_IPBC_2MUSE_HEARTBEAT_H_

