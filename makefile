socket_object = socket_object.c socket_object.h buffer_link.c buffer_link.h

socket : $(socket_object)
	gcc -c socket_object.c buffer_link.c

clean : 
	rm socket_object.o buffer_link.o