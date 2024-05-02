CC=gcc
CFLAGS=-Wall -pedantic -g3
SRCS=main.c help.c panic.c handleData.c server.c malloque.c
OBJS=$(SRCS:.c=.o)
EXEC=main

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(EXEC) $(OBJS)
