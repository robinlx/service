//////////////////////////////////////
//File: Config.cpp
//Author:   Robin.L
//Date:     2013.2.2
//Description:
//  Service�����ļ��࣬����xml��ʽ�����ļ�����Ϊȫ�ֵ����� 
/////////////////////////////////////

#include "stdafx.h"
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

Config::~Config()
{
    //�ͷż���ModuleInfoָ��
    std::vector<ModuleInfo*>::iterator iter;
    for(iter = m_ModuleList.begin(); iter != m_ModuleList.end(); /*empty*/)
    {
        ModuleInfo* temp = *iter;
        delete temp;
        iter = m_ModuleList.erase(iter);
    }
}

void Config::init(std::string configPath)
{
    std::stringstream stream;
    //�������ļ�
    TiXmlDocument conf(configPath); 
    if (!conf.LoadFile())
    {
        stream << "Failed to load config file: " << configPath << std::endl;
        throw ConfException(stream.str());
    }
    
    //��ȡ���ڵ�"IPBCService"
    TiXmlNode *root = NULL;
    root = conf.FirstChild("IPBCService");
    if (root == NULL)
    {
        stream.str("");
        stream << "Failed to load \"IPBCService\" node from config file." << std::endl;
        throw ConfException(stream.str());
    }

    //���ModuleList�ڵ�
    TiXmlNode *nodeModulelist = root->FirstChild("ModuleList");
    if (nodeModulelist == NULL)
    {
        stream.str("");
        stream << "Failed to load \"ModuleList\" node from config file." << std::endl;
        throw ConfException(stream.str());
    }

    //����Module�ڵ�
    TiXmlElement *elemModule = nodeModulelist->FirstChildElement();
    while(elemModule != NULL)
    {
        const char *enable = elemModule->Attribute("enable");
        if (ACE_OS::strcasecmp(enable, "True") == 0)    //Module������
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
    
    //��ȡLog����
    TiXmlElement *elemLog = root->FirstChildElement("Log");
    this->loadLogConf(elemLog);
}



void Config::loadLogConf(const TiXmlElement* elemLog)
{
    m_LogInfo.Debug = false;
    m_LogInfo.Size = 5;
    m_LogInfo.Backup = 10;
    m_LogInfo.Path = "";

    if (elemLog == NULL)
    {
        return;
    }

    //debug���Դ��ڲ��ҵ���true
    if (elemLog->Attribute("debug") != NULL 
        && ACE_OS::strcasecmp(elemLog->Attribute("debug"), "true") == 0)
    {
        m_LogInfo.Debug = true;
    }

    //size���Դ�������������Χ��
    int value = 0;
    if (elemLog->QueryIntAttribute("size", &value) == TIXML_SUCCESS
        && value > 0 && value <= 10)
    {
        m_LogInfo.Size = value;
    }

    //backup���Դ��ڲ�����������Χ��
    value = 0;
    if (elemLog->QueryIntAttribute("backup", &value) == TIXML_SUCCESS
        && value > 0 && value <= 20)
        
    {
        m_LogInfo.Backup = value;
    }

    //path���Դ���
    if (elemLog->Attribute("path") != NULL)
    {
        m_LogInfo.Path = elemLog->Attribute("path");
    }
}
