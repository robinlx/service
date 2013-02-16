/**
* Description
*
* Detail
*
* @project: ipbc_2Muse
* @file : IServiceMgr.h
* @date : 2011-11-10
* @author : Robin.L
*
*/


#if !defined(_IPBC_2MUSE_ISERVICEMGR_H_)
#define _IPBC_2MUSE_ISERVICEMGR_H_

#include <vector>
#include <utility>


class IModule;

class IModuleMgr
{
public:
    static IModuleMgr* CreateInstance();
    static void DestoryInstance(IModuleMgr*& pModMgr);

    virtual void Init() = 0;
    virtual void Open() = 0;
    virtual void Close() = 0;

protected:
    typedef std::pair<IModule*, HINSTANCE> ModPair;
    std::vector<ModPair> m_ModList;
};

#endif  //_IPBC_2MUSE_ISERVICEMGR_H_

