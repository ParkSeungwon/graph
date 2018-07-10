CC = g++
OBJ = $(wildcard *.o)
TOBJ = $(wildcard *.t)
EXE = $(patsubst %.x, ../%.x, $(wildcard *.x))
TST = $(patsubst %.tx, ../%.x, $(wildcard *.tx))
gtkmmLIB = $(shell pkg-config gtkmm-3.0 --libs)

all : $(EXE) $(TST)

../%.x : %.x $(OBJ)
	$(CC) -o $@ $< $(OBJ) -ljsoncpp $(gtkmmLIB)

../%.x : %.tx $(OBJ) $(TOBJ)
	$(CC) -o $@ $< $(OBJ) $(TOBJ) -ljsoncpp $(gtkmmLIB)

