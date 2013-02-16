/**
* Description
*
* Detail
*
* @project: ipbc_V3
* @file : LinuxMoudleMgr.h
* @date : 2011-11-10
* @author : Robin.L
*
*/


#if !defined(_IPBC_V3_LINUXMODULEMGR_H_)
#define _IPBC_V3_LINUXMODULEMGR_H_



#include "WinModuleMgr.h"


class LinuxModuleMgr : public WinModuleMgr
{
public:

    void Init();
    void Open();
    void Close();

};

#endif  //_IPBC_2MUSE_WINSERVICEMGR_H_

