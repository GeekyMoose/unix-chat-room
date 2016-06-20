CC			= gcc
CF_FLAG		= -Wall -g
LIBS_FLAG	= -pthread
VPATH		= src src/wunixlib
BIN			= bin

# ------------------------------------------------------------------------------
# project compilation
# ------------------------------------------------------------------------------
.PHONY: all
all: server.exe client.exe



server.exe: server.o network.o sighandler.o assets.o helper.o
	$(CC) $(CF_FLAGS) $(LIBS_FLAG) -o $@ $^
client.exe: client.o commands.o network.o sighandler.o assets.o helper.o
	$(CC) $(CF_FLAGS) $(LIBS_FLAG) -o $@ $^


server.o: server.c
	$(CC) $(CF_FLAGS) $(LIBS_FLAG) $< -c
client.o: client.c client.h commands.h
	$(CC) $(CF_FLAGS) $(LIBS_FLAG) $< -c
commands.o: commands.c commands.h client.h
	$(CC) $(CF_FLAGS) $(LIBS_FLAG) $< -c
helper.o: helper.c helper.h
	$(CC) $(CF_FLAGS) $(LIBS_FLAG) $< -c


# ------------------------------------------------------------------------------
# wunixlib compilation
# ------------------------------------------------------------------------------
sighandler.o: sighandler.c sighandler.h
	$(CC) $(CF_FLAGS) $< -c
stream.o: stream.c stream.h
	$(CC) $(CF_FLAGS) $< -c
network.o: network.c network.h
	$(CC) $(CF_FLAGS) $< -c
assets.o: assets.c assets.h
	$(CC) $(CF_FLAGS) $< -c


# ------------------------------------------------------------------------------
# Asset functions
# ------------------------------------------------------------------------------
.PHONY: clean
clean:
	-rm -rf $(BIN)
	-rm *.o
	-rm *.out
	-rm *.exe
