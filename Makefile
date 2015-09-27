CC = gcc
CFLAG = -Wall -pedantic -ansi -g
OBJ = spellcheck.o check.o
EXEC = spellcheck

${EXEC} : ${OBJ}
	${CC} ${CFLAG} ${OBJ} -o ${EXEC}

spellcheck.o :
	${CC} ${CFLAG} -c spellcheck.c

check.o : check.h
	${CC} ${CFLAG} -c check.c

clean :
	rm -rf spellcheck ${OBJ}
	rm -rf package

submission :
	mkdir package;
	tar -cvzf package/submission.tar.gz * .git* --exclude='package'
