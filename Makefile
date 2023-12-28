CC = clang

build: propel.c propel.h
	$(CC) -c propel.c
	ar rcs libpropelc.a propel.o

test: build
	$(CC) test.c -lm -L. -lpropelc -o test

run-test: test
	./test

clean:
	rm -rf ./*.o ./*.a ./test
