copesh: src/copesh.c date ls
	gcc -o copesh src/copesh.c
date: src/date.c
	gcc -o date src/date.c
ls: src/ls.c
	gcc -o ls src/ls.c
mkdir: src/mkdir.c
	gcc -o mkdir src/mkdir.c
clean:
	rm -f copesh
	rm -f date
	rm -f ls
	rm -f mkdir
test: test/SimpleFork.c
	gcc -o SimpleFork test/SimpleFork.c