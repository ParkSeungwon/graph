CFLAG = -g -c -std=c++17 -fmax-errors=1 -pthread
INCLUDE = -I../ -I../src/ 
GTK = $(shell pkg-config gtkmm-3.0 --cflags)
CC = g++
TEST_EXE = $(patsubst %.cpp, ../obj/%.tx, $(wildcard *.cpp))
TEST_OBJ = $(patsubst %.cc, ../obj/%.t, $(wildcard *.cc))

all : $(TEST_EXE) $(TEST_OBJ)

../obj/%.t : %.cc
	$(CC) $(INCLUDE) $(CFLAG) $(GTK) $< -o $@

../obj/%.tx : %.cpp
	$(CC) $(INCLUDE) $(CFLAG) $(GTK) $< -o $@
