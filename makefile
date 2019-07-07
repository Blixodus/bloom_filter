bloom: bloom.c murmur3.o
	gcc -o bloom bloom.c murmur3.o -lm

murmur3: murmur3.c
	gcc -c murmur3.c
