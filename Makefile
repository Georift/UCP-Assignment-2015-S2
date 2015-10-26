CC = gcc
CFLAG = -Wall -pedantic -ansi
OBJ = spellcheck.o check.o settings.o callback.o file.o
EXEC = spellcheck

all : ${EXEC}
debug : CFLAG += -g -DDEBUG
debug : ${EXEC}

${EXEC} : ${OBJ}
	${CC} ${CFLAG} ${OBJ} -o ${EXEC}

spellcheck.o : spellcheck.h settings.h callback.h check.h file.h
	${CC} ${CFLAG} -c spellcheck.c

callback.o : callback.h spellcheck.h
	${CC} ${CFLAG} -c callback.c

check.o : check.h
	${CC} ${CFLAG} -c check.c

settings.o : settings.h spellcheck.h
	${CC} ${CFLAG} -c settings.c

file.o : file.h spellcheck.h
	${CC} ${CFLAG} -c file.c


clean :
	rm -rf spellcheck ${OBJ}
	rm -rf package
	rm -rf docs

docs :
	doxygen Doxyfile

submission :
	mkdir package;
	tar -cvzf package/submission.tar.gz * .git* --exclude='package'
