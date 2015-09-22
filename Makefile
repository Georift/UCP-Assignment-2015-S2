CC = gcc
CFLAG = -Wall -pedantic -ansi
OBJ = spellcheck.o
EXEC = spellcheck

${EXEC} : ${OBJ}
	${CC} ${CFLAG} ${OBJ} -o ${EXEC}

spellcheck.o :
	${CC} ${CFLAG} -c spellcheck.c

clean :
	rm -rf spellcheck spellcheck.o 
