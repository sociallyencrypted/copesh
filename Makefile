copesh: src/copesh.c date
	gcc -o copesh src/copesh.c
date: src/date.c
	gcc -o date src/date.c
clean:
	rm -f copesh
	rm -f date
test: test/SimpleFork.c
	gcc -o SimpleFork test/SimpleFork.c