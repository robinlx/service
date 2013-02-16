AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=IPBCService
IPBCService_SOURCES=Config.cpp framework.cpp IDaemon.cpp IModuleMgr.cpp LinuxEntrance.cpp main.cpp WindowsEntrance.cpp WinService.cpp Consoles.cpp  HeartBeat.cpp  IEntrance.cpp  LinuxDaemon.cpp  LinuxModuleMgr.cpp  stdafx.cpp  WinModuleMgr.cpp

IPBCService_LDADD=-L$(ACE_ROOT)/lib -lACE -L$(TINYXML_ROOT)/lib -ltinyxml $(top_srcdir)/logger/.libs/liblogger.so

