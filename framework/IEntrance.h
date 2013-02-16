//////////////////////////////////////
//File: IEntrance.h
//Author:   Robin.L
//Date:     2013.1.25
//Description:
//  服务入口类程序，用于分析程序参数，基本初始化等工作
/////////////////////////////////////

#ifndef _POP_LIB_SERVICE_IENTRANCE_H_
#define _POP_LIB_SERVICE_IENTRANCE_H_

class IEntrance
{
protected:
    IEntrance()
    {
        m_Help = m_Debug = m_Config = false;
        m_AppName[0] = '\0';
    };
    ~IEntrance() {};

    
public:
    static IEntrance* CreateInstance();

    virtual void init(int argc, char **argv) = 0;
    virtual int entry() = 0;
    virtual void exit() = 0;
private:
    virtual void printUsage() = 0;
    
protected:
    bool m_Help;
    bool m_Debug;
    bool m_Config;

    std::string m_ConfigPath;
    char m_AppName[255];
};

#endif //_POP_LIB_SERVICE_IENTRANCE_H_

