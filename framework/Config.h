//////////////////////////////////////
//File: Config.h
//Author:   Robin.L
//Date:     2013.2.2
//Description:
//  Service�����ļ��࣬����xml��ʽ�����ļ�����Ϊȫ�ֵ����� 
/////////////////////////////////////

#ifndef _POP_LIB_SERVICE_CONFIG_H_
#define _POP_LIB_SERVICE_CONFIG_H_

#include <ace/Singleton.h>
#include <ace/Mutex.h>
#include <string>
#include <vector>
#include "common/Exception.h"

//����Config�쳣��
DEFINE_EXCEPTION(ConfException)

struct ModuleInfo
{
    std::string Name;
    std::string Library;
    std::string ConfigFile;
};

struct LogInfo
{
    bool Debug;
    int Size;
    int Backup;
    std::string Path;
};

class TiXmlElement;

class Config
{
public:
    Config();

    void init(std::string configPath);
    inline int moduleCount();
    inline const ModuleInfo* getModuleInfo(int indexModule);
    inline const LogInfo* getLogInfo();
private:
    void loadLogConf(const TiXmlElement* elemLog);

private:
    std::vector<ModuleInfo*> m_ModuleList;
    LogInfo m_LogInfo;
};

typedef ACE_Singleton<Config, ACE_Mutex> SVR_CONF;

/////////////////////////////////////////////
//inline function
const LogInfo* Config::getLogInfo()
{
    return &m_LogInfo;
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
#endif  //_POP_LIB_SERVICE_CONFIG_H_
