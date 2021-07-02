OBJS = hello.o add.o 
TARGET = hello.bin
$(TARGET):$(OBJS)
	gcc -o $(TARGET) $(OBJS)
*.o:*.c
	gcc -c $<
clean:
	rm *.o
	rm *.bin



