CFLAGS=-g -fsanitize=address -I . -Wall -Wextra #-Werror
# -g adds debugging information, don't use if you don't need it
# -fsanitize=address uses the address sanitizer - it is not available in
#    older versions of GCC or CLang and is not available at all in most
#    compilers that don't derive from these, so, just remove them if you're
#    using such a compiler

all: lift_arealloc_example lift_free_and_null_example lift_vec_example

lift_arealloc_example: lift_arealloc.h lift_arealloc.c examples/lift_arealloc_example.c
	$(CC) -o $@ $(CFLAGS) lift_arealloc.c examples/lift_arealloc_example.c

lift_free_and_null_example: lift_free_and_null.h lift_free_and_null.c examples/lift_free_and_null_example.c
	$(CC) -o $@ $(CFLAGS) lift_free_and_null.c examples/lift_free_and_null_example.c

lift_vec_example: lift_free_and_null.h lift_free_and_null.c lift_arealloc.h lift_arealloc.c lift_vec.h examples/lift_vec_example.c
	$(CC) -o $@ $(CFLAGS) lift_free_and_null.c lift_arealloc.c examples/lift_vec_example.c


clean:
	rm lift_arealloc_example
	rm lift_free_and_null_example
	rm lift_vec_example
