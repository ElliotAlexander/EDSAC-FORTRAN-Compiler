CC=g++


BASE_FLAGS = -std=c++14

LDFLAGS = -I/usr/local/Cellar/boost/1.69.0/include -I/opt/local/include -I include/

LLIBFLAGS = -L/usr/local/Cellar/boost/1.68.0/lib

LINKFLAGS = -lboost_thread -lboost_system -l boost_filesystem -l boost_regex -ll -lm

FLAGS = $(BASE_FLAGS) $(LLIBFLAGS) $(LDFLAGS) $(LINKFLAGS)

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

SRCS := $(call rwildcard,src/,*.cpp) $(call rwildcard,src/,*.c) 

mac:
	cd src;	bison -d parse.y --debug -t; flex lex.l
	time ./runscripts.sh
	$(CC) $(FLAGS) -o main.out $(SRCS)



# Flex was failing on strdup and fileno without this, something about a lack of POSIX support?
# TODO.
BASE_FLAGS_WIN = -std=gnu++11

LDFLAGS_WIN = -I include/ -I "C:\Users\elllz\Desktop\boost_1_60_0"

LLIBFLAGS_WIN = -L "C:\Users\elllz\Desktop\boost_1_60_0\stage\lib"

# note the specific paths, my Boost install only
LINKFLAGS_WIN =  -lm -lboost_system-mgw82-1_60 -lboost_regex-mgw82-1_60 -lboost_filesystem-mgw82-1_60

FLAGS_WIN = $(BASE_FLAGS_WIN) $(LDFLAGS_WIN)  $(LLIBFLAGS_WIN)  $(LINKFLAGS_WIN)

win:
	bison -d .\src\parse.y -t -g
	flex .\src\lex.l 
	.\scripts\ALL_HEADER_TOKENS.bat
	copy .\parse.tab.h .\src\parse.tab.h
	copy .\parse.tab.c .\src\parse.tab.c
	copy .\lex.yy.c .\src\lex.yy.c
	del /f .\parse.tab.h, .\parse.tab.c, .\lex.yy.c
	$(CC) $(FLAGS_WIN)  $(SRCS)  