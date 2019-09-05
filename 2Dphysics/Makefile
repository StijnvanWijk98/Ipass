#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := particle.cpp MPU6050.cpp MAX7219.cpp windowDecorator.cpp

# header files in this project
HEADERS := particle.hpp MPU6050.hpp MPU6050constants.hpp abstractAccelerometer.hpp simulator.hpp MAX7219constants.hpp windowDecorator.hpp MAX7219.hpp

# other places to look for files for this project
SEARCH  := ../MPU6050-Library ../MAX7219-Library ../windowDecorators

# set RELATIVE to the next higher directory 
# and defer to the appropriate Makefile.* there
RELATIVE := ..
include $(RELATIVE)/Makefile.due
