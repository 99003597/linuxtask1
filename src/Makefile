INC = -I../inc


Build: src/mystrlen.c src/bitmask.c src/myutils.c
	gcc $(INC) $^ -o $@


run:Build
	./a.out

libraries:
	make libmystring -c src
	make libmyutils -c src
	make libbitmask -c src

clean:
	rm *.o *.out