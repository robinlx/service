//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : SIPService.h
//  @ Date : 2013/2/17
//  @ Author : 
//
//


#if !defined(_COMTOM_V3_SIPSERVICE_SIPSERVICE_H_)
#define _COMTOM_V3_SIPSERVICE_SIPSERVICE_H_

#include <vector>
#include "IModule.h"

class IMsgHandle;

class SIPService : public IModule 
{
public:
    SIPService();
    void Init(const std::string& workPath);
    void Start();
    void Stop();

private:
    static void* threadFun(void* obj);
    void lisent();

private:
    bool m_ThreadSign;
    std::vector<IMsgHandle*> m_MsgHandles;
};

#endif  //_COMTOM_V3_SIPSERVICE_SIPSERVICE_H_
