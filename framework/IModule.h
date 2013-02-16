/**
* Description
*
* Detail
*
* @project: ipbc_2Muse
* @file : IModule.h
* @date : 2011-11-10
* @author : Robin.L
*
*/


#if !defined(_IPBC_2MUSE_ISERVICE_H_)
#define _IPBC_2MUSE_ISERVICE_H_


#include <string>
using std::string;

class IModule
{
public:
	static void DestroyModule(IModule*& pMod)
	{
		delete pMod;
		pMod = NULL;
	} 

	virtual void Init(const string& workPath)	{};
    virtual void Start() = 0;
    virtual void Stop() = 0;

	const string& Name()
	{
		return m_ModName;
	}

protected:
	IModule(const string& modName):m_ModName(modName) {};

protected:
	string m_ModName;
};

#endif  //_IPBC_2MUSE_ISERVICE_H_
