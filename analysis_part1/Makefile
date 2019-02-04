test:	main.o linked_list_functions.o unit_tests.o
	gcc -o test -g main.o linked_list_functions.o unit_tests.o
	
main.o:	main.c unit_tests.h
	gcc -c -g -Wall main.c
	
linked_list_functions.o:	linked_list_functions.c linked_list_functions.h
	gcc -c -g -Wall linked_list_functions.c
	
unit_tests.o:	unit_tests.c unit_tests.h
	gcc -c -g -Wall unit_tests.c
	
clean:
	rm -rf *.o
	rm -rf test
	
