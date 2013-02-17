/**
* Description
*
* Detail
*
* @project: ipbc_2Muse
* @file : WinServiceMgr.cpp
* @date : 2011-11-10
* @author : Robin.L
*
*/

#include "stdafx.h"
#include "WinModuleMgr.h"

#include "HeartBeat.h"


void WinModuleMgr::Init()
{
    //³õÊ¼»¯HeartBeatÄ£¿é
    this->initHeartBeat();

#ifdef WIN32
    typedef IModule* (__cdecl *CreateFun)(void); 
    char libPath[MAX_PATH] = {0};
	IModule* pMod = NULL;
	HINSTANCE hLibInstance = NULL;
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

        ACE_OS::snprintf(libPath, MAX_PATH, "..\\lib\\%s", modInfo->Library.c_str());
        hLibInstance = LoadLibrary(libPath);
        if (hLibInstance == NULL)
        {
            stringstream stream;
            stream << "Failed to load module: " << modInfo->Name << endl
                << "Library: " << modInfo->Library << ", Config: " << modInfo->ConfigFile;
            Logger::Error(stream.str());
            continue;
        }

        pCreateFun = (CreateFun)GetProcAddress(hLibInstance, "CreateModule");
        if (pCreateFun == NULL)
        {
            stringstream stream;
            stream << "Failed to get module process: " << modInfo->Name << endl
                << "Library: " << modInfo->Library << ", Config: " << modInfo->ConfigFile;
            Logger::Error(stream.str());
            FreeLibrary(hLibInstance);
            continue;
        }

        pMod = pCreateFun();
        if (pMod == NULL)
        {
            stringstream stream;
            stream << "Failed to create module object: " << modInfo->Name << endl
                << "Library: " << modInfo->Library << ", Config: " << modInfo->ConfigFile;
            Logger::Error(stream.str());
            FreeLibrary(hLibInstance);
            continue;
        }

        try
        {
            pMod->Init("");
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
#endif  //WIN32
}

void WinModuleMgr::Open()
{
	char logmsg[128] = {0};
	for (size_t i = 0; i < m_ModList.size(); ++i)
	{
		if (m_ModList[i].first != NULL)
		{
            try
            {
			    m_ModList[i].first->Start();
            }
            catch(Exception *e)
            {
                stringstream stream;
                stream << "Failed to start module: " << m_ModList[i].first->Name() << endl
                    << e->message();
                Logger::Error(stream.str());
                Logger::Debug(e->tostr());
                continue;
            }
            catch(...)
            {
                stringstream stream;
                stream << "Failed to start module with unknown exception: " 
                    << m_ModList[i].first->Name();
                Logger::Error(stream.str());
                continue;
            }
		}
	}
}

void WinModuleMgr::Close()
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
                FreeLibrary(m_ModList[i].second);
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

void WinModuleMgr::initHeartBeat()
{
    IModule *heartBeat = new HeartBeat;
    if (heartBeat == NULL)
    {
        throw Exception("Failed to create HeartBeat module and HeartBeat object is NULL");
    }

    m_ModList.push_back(ModPair(heartBeat, NULL));
}

