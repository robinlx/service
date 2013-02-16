
#include "stdafx.h"
#include <ace/Reactor.h>
#include "HeartBeat.h"

HeartBeat::HeartBeat(void): IModule("HeartBeat")//, m_Conn(true)
{
}

HeartBeat::~HeartBeat(void)
{
}

void HeartBeat::Start()
{
	ACE_Time_Value Delay(0);
	ACE_Time_Value Inteval(0, 100*1000);
	ACE_Reactor::instance()->schedule_timer(this, NULL, Delay, Inteval);
}

void HeartBeat::Stop()
{
	ACE_Reactor::instance()->cancel_timer(this);
}

int HeartBeat::handle_timeout( const ACE_Time_Value &current_time, const void *act /* = 0 */ )
{
	try
	{
		this->UpdateHeartBeat();
	}catch(...)
	{
		char buf[512];
		//sprintf(buf, "Failed to connect database: %s@%s:%d", 
		//	DatabaseConf::instance()->Database().c_str(), 
		//	DatabaseConf::instance()->Host().c_str(),
		//	DatabaseConf::instance()->Port());
		Logger::Debug(buf);
		return 0;
	}
	
	return 0;
}

void HeartBeat::UpdateHeartBeat()
{
	/*
	m_Conn.connect(
		DatabaseConf::instance()->Database().c_str(),
		DatabaseConf::instance()->Host().c_str(),
		DatabaseConf::instance()->Account().c_str(),
		DatabaseConf::instance()->Password().c_str(),
		DatabaseConf::instance()->Port());

	mysqlpp::Query que = m_Conn.query();
	que << "UPDATE t_svr_hbeat SET fHbeat_time = NOW() WHERE fServerId = \"" 
		<< LauncherConf::instance()->ServiceID() << "\" AND fType = " 
		<< SERVICE_TYPE << ";";
	if (que.execute().rows() == 0)
	{
		char buf[512];
		sprintf(buf, "Failed to update server heart beat ServerID:%s", LauncherConf::instance()->ServiceID().c_str());
		Logger::Debug(buf);
	}

	m_Conn.disconnect();
    */
    Logger::Debug("UpdateHeartBeat");
}
