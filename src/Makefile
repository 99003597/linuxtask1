INC = -I../inc


Build: mystrlen.c bitmask.c myutils.c
	gcc $(INC) $^ -o $@


run:Build
	./a.out

libraries:
	make libmystring -c src
	make libmyutils -c src
	make libbitmask -c src

clean:
	rm *.o *.out