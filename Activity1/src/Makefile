CFLAGS = -I../inc

libstr: mystrl.o	
	ar rc libmystring.a $^

libutil: myutils.o	
	ar rc libmyutils.a $^

libbitmask: bitmask.o 
	ar rc libbitmask.a $^

clean:	
	rm -rf *.o *.a	