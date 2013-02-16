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

class Consoles : 
    public ACE_Event_Handler
{
public:
	Consoles();
	virtual void run();

private:
	int handle_signal(int signum, siginfo_t * /* = 0 */, ucontext_t * /* = 0 */);

private:
	volatile bool m_ThreadSign;
};


#endif  //_IPBC_2MUSE_CONSOLES_H_


