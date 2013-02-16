/**
* Description
*
* Detail
*
* @project: ipbc_V3
* @file : LinuxModuleMgr.cpp
* @date : 2012-01-21
* @author : Robin.L
*
*/

#include "stdafx.h"
#include "LinuxModuleMgr.h"

#ifndef WIN32
#include <dlfcn.h>
#include "HeartBeat.h"

void LinuxModuleMgr::Init()
{
    //³õÊ¼»¯HeartBeatÄ£¿é 
    this->initHeartBeat();

    typedef IModule* (*CreateFun)(void); 
	char libPath[260] = {0};
	IModule* pMod = NULL;
    void* hLibInstance = NULL;
	CreateFun pCreateFun = NULL;
    const ModuleInfo *modInfo = NULL;
    int moduleCount = SVR_CONF::instance()->moduleCount();
	for (int i = 0; i < moduleCount; ++i)
	{
        modInfo = SVR_CONF::instance()->getModuleInfo(i); 
        if (modInfo == NULL) 
        { 
            char buf[255] = {0}; 
            ACE_OS::snprintf(buf, 255, "Failed to get %dth module", i); 
            Logger::Error(buf); 
            continue; 
        }

        ACE_OS::snprintf(libPath, 260, "../lib/%s", modInfo->Library.c_str()); 
        hLibInstance = dlopen(libPath, RTLD_LAZY); 
        if (hLibInstance == NULL) 
        { 
            stringstream stream; 
            stream << "Failed to load module: " << modInfo->Name << endl 
                << "Library: " << modInfo->Library << ", Config: " << modInfo->ConfigFile; 
            Logger::Error(stream.str()); 
            continue; 
        }
		
        pCreateFun = (CreateFun)dlsym(hLibInstance, "CreateModule"); 
        if (pCreateFun == NULL) 
        { 
            stringstream stream; 
            stream << "Failed to get module process: " << modInfo->Name << endl 
                << "Library: " << modInfo->Library << ", Config: " << modInfo->ConfigFile; 
            Logger::Error(stream.str()); 
            dlclose(hLibInstance); 
            continue; 
        }

        pMod = pCreateFun(); 
        if (pMod == NULL) 
        { 
            stringstream stream; 
            stream << "Failed to create module object: " << modInfo->Name << endl 
                << "Library: " << modInfo->Library << ", Config: " << modInfo->ConfigFile; 
            Logger::Error(stream.str()); 
            dlclose(hLibInstance); 
            continue; 
        }

        try 
        { 
            m_ModList[i].first->Init(""); 
            m_ModList.push_back(ModPair(pMod, hLibInstance)); 
        } 
        catch(Exception *e) 
        { 
            stringstream stream; 
            stream << "Failed to init module: " << modInfo->Name << endl 
                << e->message(); 
            Logger::Error(stream.str());
            Logger::Debug(e->tostr()); 
        } 
        catch(...) 
        { 
            stringstream stream; 
            stream << "Failed to init module with unknown exception: "  
                << modInfo->Name; 
            Logger::Error(stream.str()); 
        } 
 
        pMod = NULL; 
        pCreateFun = NULL; 
        hLibInstance = NULL; 
        modInfo = NULL;
	}
}

void LinuxModuleMgr::Close()
{
    char logmsg[128] = {0}; 
	for (size_t i = 0; i < m_ModList.size(); ++i) 
	{ 
		if (m_ModList[i].first != NULL) 
		{ 
            try 
            { 
                m_ModList[i].first->Stop(); 
                IModule::DestroyModule(m_ModList[i].first); 
                if (m_ModList[i].second)
                {
                    dlclose(m_ModList[i].second); 
                }
            } 
            catch(Exception *e) 
            { 
                stringstream stream; 
                stream << "Failed to stop module: " << m_ModList[i].first->Name() << endl 
                    << e->message(); 
                Logger::Error(stream.str());
                Logger::Debug(e->tostr()); 
                continue; 
            } 
            catch(...) 
            { 
                stringstream stream; 
                stream << "Failed to stop module with unknown exception: "  
                    << m_ModList[i].first->Name(); 
                Logger::Error(stream.str()); 
                continue; 
            } 
		} 
	} 
}
#endif // WIN32

