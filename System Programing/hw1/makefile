all: build run remove

build:
	gcc -o appendMeMore appendMeMore.c

run:
	./appendMeMore f1 1000000 & ./appendMeMore f1 1000000
	sleep 2
	./appendMeMore f2 1000000 x & ./appendMeMore f2 1000000 x
	ls -l f1 f2

remove:
	rm f1
	rm f2
