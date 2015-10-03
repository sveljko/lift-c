CFLAGS=-g -I . -Wall -Wextra -Werror

all: lift_arealloc_example

lift_arealloc_example: lift_arealloc.h lift_arealloc.c examples/lift_arealloc_example.c
	$(CC) -o $@ $(CFLAGS) lift_arealloc.c examples/lift_arealloc_example.c


clean:
	rm lift_arealloc_example
