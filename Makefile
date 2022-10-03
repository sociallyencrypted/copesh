copesh: src/copesh.c date ls cat mkdir
	gcc -o copesh src/copesh.c
date: src/date.c
	gcc -o date src/date.c
ls: src/ls.c
	gcc -o ls src/ls.c
mkdir: src/mkdir.c
	gcc -o mkdir src/mkdir.c
cat: src/cation.c
	gcc -o cat src/cation.c
rm: src/rm.c
	gcc -o rm src/rm.c
clean:
	rm -f copesh
	rm -f date
	rm -f ls
	rm -f mkdir
	rm -f cat
	rm -f rm
test: test/SimpleFork.c
	gcc -o SimpleFork test/SimpleFork.c