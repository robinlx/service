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
#ifdef WIN32
    typedef std::pair<IModule*, HINSTANCE> ModPair;
#else
    typedef std::pair<IModule*, void*> ModPair;
#endif //WIN32
    std::vector<ModPair> m_ModList;
};

#endif  //_IPBC_2MUSE_ISERVICEMGR_H_

