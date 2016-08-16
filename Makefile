
CC:=g++
LD:=g++
CPPFLAGS:=-std=c++11
CFLAGS:=
LDFLAGS:=

PROJ:=Aria
COMMON:=Common
DATA:=Data
ALGO:=Algorithm
ENGINE:=Engine

LINK_SHARED:=-shared
BUILDING_DLL:=BUILDING_DLL
BOOST_LINK_OPT:=BOOST_ALL_DYN_LINK

MODULE:=
INCL:=
DEF_BUILD_DLL:=-D$(BUILDING_DLL) -D$(BOOST_LINK_OPT)

ROOT:=$(CURDIR)
GEN:=Debug
BIN:=bin
BIN_DIR:=$(ROOT)/$(BIN)
COMMON_DIR:=$(ROOT)/$(COMMON)/
PYTHON_INCLUDE_DIR:=/usr/include/python2.7 

LDFLAGS_PYTHON:=-lpython2.7
LDFLAGS_BOOST_SYSTEM:=-lboost_system 
LDFLAGS_BOOST_FILESYSTEM:=-lboost_filesystem 
LDFLAGS_BOOST_LOG:=-lboost_log 
LDFLAGS_BOOST_THREAD:=-lboost_thread 
LDFLAGS_BOOST_PYTHON:=-lboost_python
LDFLAGS_BOOST_DATETIME:=-lboost_date_time

COMPONENTS:=$(DATA) $(ALGO) $(ENGINE) $(PROJ)
COMPONENTS_CLEAN:=$(patsubst %, %.clean, $(COMPONENTS))
COMPONENTS_SHOW:=$(patsubst %, %.show, $(COMPONENTS))

export

all: $(COMPONENTS)

.PHONY: all $(COMPONENTS)

$(COMPONENTS): %:
	$(MAKE) -C $@

$(COMPONENTS_CLEAN): %:
	$(MAKE) -C $(patsubst %.clean, %, $@) clean

$(COMPONENTS_SHOW): %:
	$(MAKE) -C $(patsubst %.show, %, $@) show

clean: $(COMPONENTS_CLEAN)
	rm -rf $(BIN_DIR)/*

