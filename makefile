##############################################
#	SUBDIRS MAKEFILE	
#	author: Siyu Jian 
#	emal:   jiansiyu@gmail.com
#
#		Physics Department of UNiversity of Virginia
#		Charlottesville, VA, 22903
#		United States
##############################################


#+++++++++++++++++++++++++++++++++++++++++++
# You make need to modify the following paths according to you system setting
#+++++++++++++++++++++++++++++++++++++++++++

#------------------------------------------------------------------------------
SOURCEPATH  =  analysis src GEMDeccoder GUIDialog src
srf         =  c cpp cxx C CPP

#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# general make file configuration
CC       = g++ -std=c++0x -pthread -O3 -g3 #-Wall

# ROOT related configuration
ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLDFLAGS  := $(shell root-config --ldflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)
ROOTHASTHREAD    := $(shell root-config --has-thread)
ROOTAUXLIB       := $(shell root-config --auxlibs)
ROOTAUXCFLAG     := $(shell root-config --auxcflags)
#------------------------------------------------------------------------------


CXXFLAGS  +=${ROOTCFLAGS} -I${CODA}/Linux-x86_64/include
LDFLAGS	  +=${ROOTLDFLAGS}
LIBS      +=${ROOTLIBS} ${ROOTGLIBS} -lMinuit -L${CODA}/Linux-x86_64/lib -levioxx -levio -lexpat 
GLIBS     +=${ROOTGLIBS} ${SYSLIBS}
LINKOPTION += -pthread -lm -ldl -lconfig++

OBJS	+= $(addprefix ./bin/analysis/, $(notdir ${patsubst %.cpp, %.o, ${wildcard ./analysis/*.cpp}}))
OBJS	+= $(addprefix ./bin/analysis/, $(notdir ${patsubst %.C, %.o, ${wildcard ./analysis/*.C}}))
OBJS	+= $(addprefix ./bin/analysis/, $(notdir ${patsubst %.cxx, %.o, ${wildcard ./analysis/*.cxx}}))

OBJS	+= $(addprefix ./bin/GEMDecoder/, $(notdir ${patsubst %.cpp, %.o, ${wildcard ./GEMDecoder/*.cpp}}))
OBJS	+= $(addprefix ./bin/GUIDialog/, $(notdir ${patsubst %.cpp, %.o, ${wildcard ./GUIDialog/*.cpp}}))
OBJS	+= $(addprefix ./bin/src/, $(notdir ${patsubst %.cpp, %.o, ${wildcard ./src/*.cpp}}))

TARGET = ROOT_GUI
all: ${TARGET}
THIS_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

ROOT_GUI: ${OBJS} 
	@echo ${THIS_DIR}
	@echo ${OBJS}
	@echo 'Building target: $@' 
	@$(CC)  $(OBJS)  $(LIBS) ${LIBS}  ${LINKOPTION} -o  "ROOT_GUI"
	@echo 'Finish building: $<'
	@echo

./bin/analysis/%.o : ./analysis/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	@$(CC)  ${CXXFLAGS} -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finish building: $<'
	@echo
	
./bin/analysis/%.o : ./analysis/%.C
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	@$(CC)  ${CXXFLAGS} -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finish building: $<'
	@echo	
	
./bin/analysis/%.o : ./analysis/%.cxx
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	@$(CC)  ${CXXFLAGS} -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finish building: $<'
	@echo
	
./bin/GEMDecoder/%.o : ./GEMDecoder/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	@$(CC)  ${CXXFLAGS} -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finish building: $<'
	@echo
	
./bin/GUIDialog/%.o : ./GUIDialog/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	@$(CC)  ${CXXFLAGS} -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finish building: $<'
	@echo
	
./bin/src/%.o : ./src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	@$(CC)  ${CXXFLAGS} -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finish building: $<'
	@echo	
	
PHONY: clean

clean:
	${RM} ${OBJS} ${TARGET} *~	
	
