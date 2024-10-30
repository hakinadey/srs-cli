CC = gcc
CFLAGS = -Wall -g
SRCS = src/main.c src/student.c src/course.c src/controller.c
TARGET = bin/srs

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

run:
	bin/srs

purge:
	rm -f bin/srs data/*.csv
