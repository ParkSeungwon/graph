CFLAG = -g -c -std=c++11 -fmax-errors=1 -lpthread 
INCLUDE = -I../ -I../src -I/usr/include/libdrm -I/usr/include/GL
#GTKCFLAG = $(shell pkg-config gtkmm-3.0 --cflags) #-I$(ROOT)
CC = g++
OBJ = $(patsubst %.cc, ../obj/%.o, $(wildcard *.cc))
MAIN_OBJ = $(patsubst %.cpp, ../obj/%.x, $(wildcard *.cpp))

all : $(OBJ) $(MAIN_OBJ)

../obj/%.o : %.cc 
	$(CC) $(INCLUDE) $(CFLAG) $< -o $@

../obj/%.x : %.cpp
	$(CC) $(INCLUDE) $(CFLAG) $< -o $@

