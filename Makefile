PHONY: run clean

run: test
	./test | diff - test.out

test.out test.c: README.md doctest.py
	./doctest.py README.md test.out > test.c

test: list.c algorithm.c test.c
	gcc test.c list.c algorithm.c -o test

clean:
	rm test*
