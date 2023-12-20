.SUFFIXES: .c .o
CCFLAGS = -std=c99 -pedantic -Wall
OBJS = scapegoat.o func.o
EXEC = scapegoat 
OPTIONS = -g

build: ${OBJS}
	gcc ${CCFLAGS} ${OPTIONS} -o ${EXEC} ${OBJS} -lm
	
scapegoat.o: scapegoat.c func.h
	gcc ${CCFLAGS} ${OPTIONS} -c scapegoat.c -lm
	
func.o: func.c func.h
	gcc ${CCFLAGS} ${OPTIONS} -c func.c -lm
	
run: ${EXEC}
	./${EXEC}
	
clean:
	rm -f ${EXEC} ${OBJS}

valgrind:
	#valgrind ./${EXEC}
	#valgrind --tool=memcheck --leak-check=full ./${EXEC}
	valgrind --track-origins=yes --leak-check=full ./${EXEC}
	
