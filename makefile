main: main.c bloom.o murmur3.o
	gcc -o main main.c bloom.o murmur3.o -lm

bloom: bloom.c murmur3.o
	gcc -c bloom bloom.c murmur3.o -lm

murmur3: murmur3.c
	gcc -c murmur3.c
