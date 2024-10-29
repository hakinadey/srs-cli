CC = gcc
CFLAGS = -Wall -g
SRCS = main.c student.c course.c controller.c
TARGET = srs

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
