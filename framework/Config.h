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

class Config
{
public:
    Config();

    void init(std::string configPath);
    int moduleCount();
    const ModuleInfo* getModuleInfo(int indexModule);

private:
    std::vector<ModuleInfo*> m_ModuleList;
};

typedef ACE_Singleton<Config, ACE_Mutex> SVR_CONF;

#endif  //_POP_LIB_SERVICE_CONFIG_H_

