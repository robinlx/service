AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=IPBCService
IPBCService_SOURCES=main.cpp IEntrance.cpp LinuxEntrance.cpp Config.cpp LinuxDaemon.cpp Consoles.cpp
IPBCService_LDADD=-L$(ACE_ROOT)/lib -lACE -L$(TINYXML_ROOT)/lib -ltinyxml $(top_srcdir)/logger/.libs/liblogger.so

