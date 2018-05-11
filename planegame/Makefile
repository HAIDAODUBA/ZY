CC=gcc

TARGET=main

RCSR = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(RCSR))

LINK += -lpthread
LINK += -lcurses

$(TARGET):$(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LINK)

$(OBJS):%.o:%.c
	$(CC) -c $^ -o $@

clean:
	rm *.o $(TARGET)