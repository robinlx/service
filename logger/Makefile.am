ACE_ROOT=/usr/local/ACE
INCLUDES=-I$(ACE_ROOT)/include/ -I$(top_srcdir)/common 

AUTOMAKE_OPTIONS=foreign
lib_LTLIBRARIES=liblogger.la
liblogger_la_SOURCES=ConsoleLog.cpp DllMain.cpp EngineMaker.cpp FileLog.cpp Logger.cpp LogService.cpp
liblogger_la_LDFLAGS=-shared -fPIC -version-info 1:0:0
liblogger_la_LIBADD=$(ACE_ROOT)/lib/libACE.so
include_HEADERS=Logger.h

