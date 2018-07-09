all : 
	make -C gtk/
	make -C src/
	make -C gl/
	make -C tst/
	make -C obj/

PHONY : clean

clean :
	rm obj/*.o obj/*.x *.x

ls :
	echo $(EXE)
