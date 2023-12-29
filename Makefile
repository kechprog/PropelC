CC = clang

build: src/*
	$(CC) -c src/propel.c src/propel_matr.c -I./src
	ar rcs libpropelc.a propel.o propel_matr.o

test: build
	$(CC) test.c -lm -L. -lpropelc -I./src -o test

run-test: test
	./test

clean:
	rm -rf ./*.o ./*.a ./test
