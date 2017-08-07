TARGET=wc_alias
CC=gcc
CFLAGS=-g -Wall


all: $(TARGET) simple_line_count
	rm -rf *.o

$(TARGET): wc_alias.o
	$(CC) $(CFLAGS) wc_alias.o -o $(TARGET)

wc_alias.o: ./wc_alias.c
	$(CC) $(CFLAGS) -c ./wc_alias.c 


simple_line_count: simple_line_count.o

simple_line_count.o: ./simple_line_count.c
	$(CC) $(CFLAGS) -c ./simple_line_count.c

clean:
	rm -rf *.o $(TARGET) simple_line_count
