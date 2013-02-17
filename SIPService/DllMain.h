
#if !defined(_COMTOM_V3_SIPSERVICE_DLLMAIN_H_)
#define _COMTOM_V3_SIPSERVICE_DLLMAIN_H_


#define MOD_EXPORT

#ifdef WIN32
    #ifdef MOD_EXPORT
        #define MODAPI __declspec(dllexport)
    #else
        #define MODAPI __declspec(dllimport)
    #endif // MOD_EXPORT
#else	//WIN32
    #define MODAPI
#endif	//WIN#@

class IModule;

extern "C"
{
    MODAPI IModule* CreateModule();

    MODAPI void DestroyModule(IModule*& pMod);
};

#endif  //_COMTOM_V3_SIPSERVICE_DLLMAIN_H_
