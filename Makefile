CC = gcc
CFLAGS = -Wall -g
SRCS = main.c student.c course.c
TARGET = srs

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
