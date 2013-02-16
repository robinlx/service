/**
* Description
*
* Detail
*
* @project: ipbc_2Muse
* @file : IDaemon.h
* @date : 2011-11-10
* @author : Robin.L
*
*/


#if !defined(_IPBC_2MUSE__IDAEMON_H_)
#define _IPBC_2MUSE__IDAEMON_H_



class IModuleMgr;

class IDaemon
{
public:
    enum SRV_TYPE
    {
        SRV_Service,
        SRV_Consoles
    };
    static IDaemon* CreateInstance(SRV_TYPE svrType);
    static void DestoryInstance(IDaemon*& pSrv);

	IDaemon();
    virtual void Start();
    virtual void Stop();
    virtual void Setup();
    virtual void Remove();
	virtual void Run();

protected:
    virtual void openModuleMgr();
protected:
	IModuleMgr* m_ModMgr;
    volatile bool m_ThreadSign;
};





#endif  //_IPBC_2MUSE__IDAEMON_H_
