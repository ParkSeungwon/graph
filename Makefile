all : 
	make -C src/
	make -C gtk/
#	make -C gl/
	make -C tst/
	make -C obj/
	./catch.x

PHONY : clean

clean :
	rm obj/*.o obj/*.x *.x

ls :
	echo $(EXE)
