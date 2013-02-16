/**
* Description
*
* Detail
*
* @project: ipbc_2Muse
* @file : Consoles.h
* @date : 2011-11-10
* @author : Robin.L
*
*/


#if !defined(_IPBC_2MUSE_CONSOLES_H_)
#define _IPBC_2MUSE_CONSOLES_H_

#include <ace/Event_Handler.h>
#include "IDaemon.h"

class Consoles 
    : public IDaemon
{
public:
	Consoles();
	virtual void Start();
    virtual void Stop();

};


#endif  //_IPBC_2MUSE_CONSOLES_H_


