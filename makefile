TARGET = timeout
LIBS = -lncurses
CC = gcc
CFLAGS = -g -Wall

SRCS = timeout.c countdown.c config.c input.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(LIBS) -o $(TARGET) $(SRCS)

clean:
	$(RM) $(TARGET)
