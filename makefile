CC=gcc

jiaowu=main.c tea_f.c stu_f.c

CFLAGS=-Wall -g

OBJS=$(jiaowu:.c=.o)

TARGET=my_program

build:$(TARGET)


$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

run:$(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
