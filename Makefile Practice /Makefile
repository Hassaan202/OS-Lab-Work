output: main.o message.o
	gcc main.o message.o -o output

main.o: main.c
	gcc -c main.c

message.o: message.c
	gcc -c message.c

clean:
	rm *.o output a.out


#Format:
#Target: Dependencies
#	Action
#statement means that message.o is recompiled if message.c is modified and output recompiled if main.o and 
#message.o is modified
#
#
#
#