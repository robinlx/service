//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : UserMgr.h
//  @ Date : 2013/2/17
//  @ Author : 
//
//


#if !defined(_COMTOM_V3_SIPSERVICE_USERMGR_H_)
#define _COMTOM_V3_SIPSERVICE_USERMGR_H_

#include <list>
#include "IMsgHandle.h"

class IUser;

class UserMgr 
    : public IMsgHandle 
{
public:
    IUser* getUser();
    virtual bool handleMsg();
private:
    std::list<IUser*> m_UserList;
};

#endif  //_COMTOM_V3_SIPSERVICE_USERMGR_H_
