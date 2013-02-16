/**
* Description
*
* Detail
*
* @project: ipbc_2Muse
* @file : WinServiceMgr.h
* @date : 2011-11-10
* @author : Robin.L
*
*/


#if !defined(_IPBC_2MUSE_WINSERVICEMGR_H_)
#define _IPBC_2MUSE_WINSERVICEMGR_H_



#include "IModuleMgr.h"


class WinModuleMgr : public IModuleMgr
{
public:
    virtual void Init();
    virtual void Open();
    virtual void Close();

protected:
    virtual void initHeartBeat();
};

#endif  //_IPBC_2MUSE_WINSERVICEMGR_H_
