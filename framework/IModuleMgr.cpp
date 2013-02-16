
#include "stdafx.h"
#include "IModuleMgr.h"
#include "WinModuleMgr.h"
#include "LinuxModuleMgr.h"

IModuleMgr* IModuleMgr::CreateInstance()
{
#ifdef WIN32
	return new WinModuleMgr;
#else
	return new LinuxModuleMgr;
#endif // WIN32
}

void IModuleMgr::DestoryInstance( IModuleMgr*& pModMgr )
{
	delete pModMgr;
	pModMgr = NULL;
}

