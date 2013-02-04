AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=IPBCService
IPBCService_SOURCES=main.cpp IEntrance.cpp LinuxEntrance.cpp Config.cpp
IPBCService_LDADD=-L$(ACE_ROOT)/lib -lACE -L$(TINYXML_ROOT)/lib -ltinyxml $(SUPPORT_ROOT)/logger/.libs/liblogger.so

