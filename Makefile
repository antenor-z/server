CC=gcc
CFLAGS=-Wall -pedantic -pthread
SRCS=dequeue.c enqueue.c getFileType.c handleData.c insertLog.c insertStats.c main.c queue.c server.c utils.c debug.c
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
	rm -f *.log
	rm -f *.txt

run: ${EXEC}
	./${EXEC} -p ${PORT} -r ${ROOT_DIR} -l ./log.log -s ./stats.txt

run-verbose: ${EXEC}
	./${EXEC} -p ${PORT} -r ${ROOT_DIR} -l ./log.log -s ./stats.txt -v

run-background: ${EXEC}
	./${EXEC} -p ${PORT} -r ${ROOT_DIR} -l ./log.log -s ./stats.txt -b

mem-check: ${EXEC}
	valgrind --leak-check=full ./${EXEC} -p ${PORT} -r ${ROOT_DIR} -l ./log.log -s ./stats.txt -v