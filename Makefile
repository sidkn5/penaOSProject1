CC = gcc
CFLAGS = -g
TARGET = doenv
OBJS = doenv.o

$(TARGET):$(OBJS)
	$(CC) -o $@ $(OBJS)
.c.o:
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f *.o $(TARGET)




