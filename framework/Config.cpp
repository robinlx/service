//////////////////////////////////////
//File: Config.cpp
//Author:   Robin.L
//Date:     2013.2.2
//Description:
//  Service配置文件类，加载xml格式配置文件，作为全局单例。 
/////////////////////////////////////

#include "Config.h"
#include <ace/OS.h>
#include <iostream>
#define TIXML_USE_STL
#include <tinyxml/tinyxml.h>

#include "logger/Logger.h"
#include "common/Exception.h"

Config::Config()
{
    //Empty function
}

void Config::init(std::string configPath)
{
    std::stringstream stream;
    //打开配置文件
    TiXmlDocument conf(configPath); 
    if (!conf.LoadFile())
    {
        stream << "Failed to load config file: " << configPath << std::endl;
        throw ConfException(stream.str());
    }
    
    //获取根节点"IPBCService"
    TiXmlNode *root = NULL;
    root = conf.FirstChild("IPBCService");
    if (root == NULL)
    {
        stream.str("");
        stream << "Failed to load \"IPBCService\" node from config file." << std::endl;
        throw ConfException(stream.str());
    }

    //获得ModuleList节点
    TiXmlNode *nodeModulelist = root->FirstChild("ModuleList");
    if (nodeModulelist == NULL)
    {
        stream.str("");
        stream << "Failed to load \"ModuleList\" node from config file." << std::endl;
        throw ConfException(stream.str());
    }

    //遍历Module节点
    TiXmlElement *elemModule = nodeModulelist->FirstChildElement();
    while(elemModule != NULL)
    {
        const char *enable = elemModule->Attribute("enable");
        if (ACE_OS::strcasecmp(enable, "True") == 0)    //Module被启用
        {
            ModuleInfo *info = new ModuleInfo;
            const char *tmpName = elemModule->Attribute("name");
            const char *tmpLibrary = elemModule->Attribute("library");
            if (tmpName == NULL || tmpLibrary == NULL)
            {
                delete info;
                continue;
            }

            const char *tmpConfig = elemModule->Attribute("config");
            if (tmpConfig != NULL)
            {
                info->ConfigFile = tmpConfig;
            }
            else
            {
                info->ConfigFile = "";
            }

            m_ModuleList.push_back(info);
        }
       
        elemModule = elemModule->NextSiblingElement();
    }
    
}

int Config::moduleCount()
{
    return m_ModuleList.size();
}

const ModuleInfo* Config::getModuleInfo(int indexModule)
{
    if (indexModule < 0 || indexModule >= m_ModuleList.size())
    {
        return NULL;
    }

    return m_ModuleList[indexModule];
}
