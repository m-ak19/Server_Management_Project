CC = gcc
CFLAGS = -W -Wall -O3
TARGET = system

system: main.o synchro_list.o
	$(CC) -o $(TARGET) main.o synchro_list.o

synchro_list.o: synchro_list.c synchro_list.h
	$(CC) -c synchro_list.c $(CFLAGS) -o synchro_list.o

main.o: main.c synchro_list.h
	$(CC) -c main.c $(CFLAGS) -o main.o

clean:
	rm -rf *.o
	rm -rf $(TARGET)
