CC=gcc
CFLAGS=-Wall -pedantic -g3
SRCS=main.c help.c panic.c handleData.c server.c malloque.c bye.c insertLog.c enqueue.c dequeue.c datetime.c insertStats.c debug.c
OBJS=$(SRCS:.c=.o)
EXEC=a4server
PORT=5000
ROOT_DIR=./test

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(EXEC) $(OBJS)

run: ${EXEC}
	./${EXEC} -p ${PORT} -r ${ROOT_DIR} -l log.log -s stats.txt
