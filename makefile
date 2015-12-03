TARGET = timeout
LIBS = -lncurses -lcrypto
CC = gcc
CFLAGS = -g -Wall

SRCS = timeout.c countdown.c config.c draw.c input.c utils.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(LIBS) -o $(TARGET) $(SRCS)

clean:
	$(RM) $(TARGET)
