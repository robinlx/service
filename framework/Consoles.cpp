/**
* Description
*
* Detail
*
* @project: ipbc_2Muse
* @file : Consoles.cpp
* @date : 2011-11-10
* @author : Robin.L
*
*/
#include "stdafx.h"
#include "Consoles.h"


Consoles::Consoles()
{
	m_ThreadSign = false;
}

void Consoles::Start()
{
    stringstream stream;
    stream << "Run " << APP_NAME << " with console.";
    Logger::Info(stream.str());

    this->openModuleMgr();

    stream.str("");
    stream << "Stop " << APP_NAME;
    Logger::Info(stream.str());
}

void Consoles::Stop()
{
    m_ThreadSign = false;
}



