# makefile
# OBJ_FILE = hello.o add.o
# hello.bin:$(OBJ_FILE)
#	gcc $^ -o $@
# clean:
#	rm *.o
# .PHONY:clean
mymath:add.c
	gcc -c -fPIC add.c 
	gcc -shared -o libmymath.so add.o
	gcc hello.c -L. -lmymath -o hello.bin 

install:
	@sudo mv libmymath.so /usr/lib

hello.bin:hello.c 
	gcc hello.c -lmymath

clean:
	-rm *.o
.PHONY:clean



