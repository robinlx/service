//////////////////////////////////////
//File: Config.h
//Author:   Robin.L
//Date:     2013.2.2
//Description:
//  Service配置文件类，加载xml格式配置文件，作为全局单例。 
/////////////////////////////////////

#ifndef _POP_LIB_SERVICE_CONFIG_H_
#define _POP_LIB_SERVICE_CONFIG_H_

#include <ace/Singleton.h>
#include <ace/Mutex.h>
#include <string>
#include <vector>
#include "common/Exception.h"

//定义Config异常类
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
    ~Config();

    void init(std::string configPath);
    inline int moduleCount() const;
    inline const ModuleInfo* getModuleInfo(int indexModule) const;
    inline const LogInfo* getLogInfo() const;
private:
    void loadLogConf(const TiXmlElement* elemLog);

private:
    std::vector<ModuleInfo*> m_ModuleList;
    LogInfo m_LogInfo;
};

typedef ACE_Singleton<Config, ACE_Mutex> SVR_CONF;

/////////////////////////////////////////////
//inline function
const LogInfo* Config::getLogInfo() const
{
    return &m_LogInfo;
}

int Config::moduleCount() const
{
    return m_ModuleList.size();
}

const ModuleInfo* Config::getModuleInfo(int indexModule) const
{
    if (indexModule < 0 || indexModule >= static_cast<int>(m_ModuleList.size()))
    {
        return NULL;
    }

    return m_ModuleList[indexModule];
}
#endif  //_POP_LIB_SERVICE_CONFIG_H_

