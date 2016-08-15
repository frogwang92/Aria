
CC:=g++
LD:=g++
CPPFLAGS:=-c -std=c++11
LDFLAGS:=

PROJ:=Aria
COMMON:=Common
DATA:=Data

ROOT:=$(CURDIR)
TEMPOUTPUTDIR:=Debug
BIN:=bin
BIN_DIR:=$(ROOT)/$(BIN)/
COMMON_DIR:=$(ROOT)/$(COMMON)/
PYTHON_INCLUDE_DIR:=/usr/include/python2.7/ 

CPP_SOURCE:=$(wildcard *.cpp)

BUILDING_DLL:=BUILDING_DLL
BOOST_LINK_OPT:=BOOST_ALL_DYN_LINK

export

.PHONY: all clean

all:
	$(MAKE) -C $(DATA)

clean:
	rm -rf $(BIN_DIR)*
	$(MAKE) -C $(DATA) clean

