CC=gcc
CFLAGS=-Wall -pedantic
SRCS=main.c help.c panic.c handleData.c server.c
OBJS=$(SRCS:.c=.o)
EXEC=main

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(EXEC) $(OBJS)
