#Someone can work with neither autotools nor cmake
CC=gcc
C_FLAGS=-Wall -Wextra -fPIC -O2
OBJS= vmath.o addition.o matr.o figure.o
test: testm.c libvmath.so
	gcc -L. testm.c -lvmath -o test
libvmath.so: $(OBJS)
	gcc --shared -lm $(OBJS) -o libvmath.so
%.o:%.c vmath.h
	$(CC) -c $< $(C_FLAGS)
