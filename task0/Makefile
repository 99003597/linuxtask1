PROJECT_NAME = ASSIGNMENT1

SRC = src/mystrl.c\
src/bitmask.c\
src/myutils.c\
test.c\

INC = -Iinc

$(PROJECT_NAME).out: $(SRC)
	gcc $^ -o $@ $(INC)

run: $(PROJECT_NAME).out
	./$^

libraries:
	make libmystrl -C src
	make libmyutils -C src
	make libbitmask -C src
		
clean:	
	rm -rf *.o *.out	