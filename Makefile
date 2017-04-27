# Target
TARGET = PqTest

# C++(.cpp) source files
TARGET_CPP_SOURCES = \
	 MyTask.cpp \
	 Message.cpp \
	 Router.cpp \
	 PriorityQueue.cpp \
	 ATask.cpp \
	 BTask.cpp \
	 DisplayTask.cpp \
	 Saftey.cpp \
	 Main.cpp
	

# TOPPERS/ATK(OSEK) config file
TOPPERS_OSEK_OIL_SOURCE = Main.oil

# don't change this macro
O_PATH ?= build

# makefile for C++(.cpp) build
include ../../ecrobot/ecrobot++.mak
