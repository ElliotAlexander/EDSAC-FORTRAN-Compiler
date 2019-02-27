CC=g++

BASE_FLAGS = -std=c++14

LDFLAGS = -I/usr/local/Cellar/boost/1.69.0/include -I/opt/local/include -I include/

LLIBFLAGS = -L/usr/local/Cellar/boost/1.68.0/lib

LINKFLAGS = -lboost_thread -lboost_system -l boost_filesystem -l boost_regex -ll -lm

FLAGS = $(BASE_FLAGS) $(LLIBFLAGS) $(LDFLAGS) $(LINKFLAGS)

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

SRCS := $(call rwildcard,src/,*.cpp) $(call rwildcard,src/,*.c) 


all:
	cd src;	bison -d parse.y --debug -t; flex lex.l
	cd ..
	time ./runscripts.sh
	$(CC) $(FLAGS) -o main.out $(SRCS)
