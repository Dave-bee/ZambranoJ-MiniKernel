CC = gcc

CFLAGS = -Wall -Wextra -g

INCLUDES = -Iinclude

LIBS = -lpthread -lm

SRC = \
	src/main.c \
	src/queue.c \
	src/cpu.c \
	src/metrics.c

OBJ = $(SRC:.c=.o)

TARGET = minikernel


all: $(TARGET)


$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $(TARGET) $(LIBS)


%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


clean:
	rm -f $(OBJ) $(TARGET)


run: all
	./minikernel


test:
	$(CC) $(CFLAGS) $(INCLUDES) \
	tests/test_queue.c src/queue.c \
	-o tests/test_queue $(LIBS)

	./tests/test_queue
