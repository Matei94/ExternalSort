.PHONY : build clean

build : tema5.c
	gcc -o tema5 tema5.c -Wall
	
clean :
	rm -f tema5 f1.dat f2.dat
