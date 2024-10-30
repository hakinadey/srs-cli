CC = gcc
CFLAGS = -Wall -g
SRCS = src/*.c
TARGET = bin/srs

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

run:
	bin/srs

purge:
	rm -f bin/srs data/*.csv
