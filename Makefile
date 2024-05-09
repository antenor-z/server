CC=gcc
CFLAGS=-Wall -pedantic -g3
SRCS=main.c help.c panic.c handleData.c server.c malloque.c bye.c logger.c enqueue.c dequeue.c datetime.c stats.c
OBJS=$(SRCS:.c=.o)
EXEC=main

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(EXEC) $(OBJS)
