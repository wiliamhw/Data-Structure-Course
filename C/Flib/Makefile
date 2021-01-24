CC = gcc
CFLAGS = -Wall
DEPS = utility.h sorter.h cs50.h
OBJ = Atest.o utility.o sorter.o cs50.o

%.o: %.c $(DEPS)
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -c -o $@ $<

go: $(OBJ)
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o $@ $^

# speller:
# 	clang -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -c -o speller.o speller.c
# 	clang -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -c -o dictionary.o dictionary.c
# 	clang -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -o speller speller.o dictionary.o
