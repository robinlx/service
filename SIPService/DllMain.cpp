// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"




#ifdef WIN32
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

#endif // WIN32

//////////////////////////////////////////////////////////////////////
#include "DllMain.h"
#include "IModule.h"
#include "SIPService.h"


IModule* CreateModule()
{
    return new SIPService;
}


void DestroyModule(IModule*& pMod)
{
    IModule::DestroyModule(pMod);
}