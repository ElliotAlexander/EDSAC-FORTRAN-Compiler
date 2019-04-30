CC=g++


BASE_FLAGS = -std=c++14

LDFLAGS = -I/usr/local/Cellar/boost/1.69.0/include -I/opt/local/include -I include/

LLIBFLAGS = -L/usr/local/Cellar/boost/1.68.0/lib

LINKFLAGS = -lboost_thread -lboost_system -l boost_filesystem -l boost_regex -ll -lm

FLAGS = $(BASE_FLAGS) $(LLIBFLAGS) $(LDFLAGS) $(LINKFLAGS)

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

SRCS := $(call rwildcard,src/,*.cpp) $(call rwildcard,src/,*.cc) 

mac:
	cd src;	bison -d parse.y -o parse.tab.cc --debug -t; flex -o lex.flex.cc lex.l
	time ./runscripts.sh
	$(CC) $(FLAGS) -o edsac.out $(SRCS)


CC_LINUX=g++


BASE_FLAGS_LINUX = -std=c++14 -static

LDFLAGS_LINUX = -Iboost_1_69_0/installation/include -I include/ -L /usr/lib

LLIBFLAGS_LINUX = -Lboost_1_69_0/installation/lib 

LINKFLAGS_LINUX = -lboost_system  -lboost_thread -lboost_filesystem -lboost_regex -lpthread -ll -lm 

FLAGS_LINUX =   $(BASE_FLAGS_LINUX)  $(LDFLAGS_LINUX) $(LLIBFLAGS_LINUX)  $(LINKFLAGS_LINUX)

SRCS_LINUX := $(call rwildcard,src/,*.cpp) $(call rwildcard,src/,*.cc) 

linux:
	cd src;	bison -d parse.y -o parse.tab.cc --debug -t; flex -o lex.flex.cc lex.l
	time ./runscripts.sh
	$(CC_LINUX) $(FLAGS_LINUX) -o out/linux/edsac.out $(SRCS_LINUX)
