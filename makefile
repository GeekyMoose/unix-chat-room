CC			= gcc
CF_FLAG		= -Wall -g
LIBS_FLAG	= -pthread
VPATH		= src src/wunixlib
BIN			= bin

# ------------------------------------------------------------------------------
# project compilation
# ------------------------------------------------------------------------------
.PHONY: all
all: server.o client.o

server.o: server.c network.o
	$(CC) $(CF_FLAGS) -o $@ $^
client.o: client.c
	$(CC) $(CF_FLAGS) -o $@ $^


# ------------------------------------------------------------------------------
# wunixlib compilation
# ------------------------------------------------------------------------------
wunixlib.o: sighandler.o stream.o network.o
	$(CC) $(CF_FLAGS) -o $@ $^ -c

sighandler.o: sighandler.c sighandler.h
	$(CC) $(CF_FLAGS) -o $@ $< -c
stream.o: stream.c stream.h
	$(CC) $(CF_FLAGS) -o $@ $< -c
network.o: network.c network.h
	$(CC) $(CF_FLAGS) -o $@ $< -c


# ------------------------------------------------------------------------------
# Asset functions
# ------------------------------------------------------------------------------
.PHONY: clean
clean:
	-rm -rf $(BIN)
	-rm *.o
	-rm *.out
	-rm *.exe
