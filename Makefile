CC = gcc
CFLAG = -Wall -pedantic -ansi
OBJ = spellcheck.o check.o settings.o callback.o file.o list.o
EXEC = spellcheck

all : ${EXEC}
debug : CFLAG += -g -DDEBUG
debug : ${EXEC}

${EXEC} : ${OBJ}
	${CC} ${CFLAG} ${OBJ} -o ${EXEC}

spellcheck.o : spellcheck.h settings.h callback.h check.h file.h list.h
	${CC} ${CFLAG} -c spellcheck.c

callback.o : callback.h spellcheck.h
	${CC} ${CFLAG} -c callback.c

check.o : check.h
	${CC} ${CFLAG} -c check.c

settings.o : settings.h spellcheck.h
	${CC} ${CFLAG} -c settings.c

file.o : file.h spellcheck.h
	${CC} ${CFLAG} -c file.c

list.o : list.h
	${CC} ${CFLAG} -c list.c

clean :
	rm -rf spellcheck ${OBJ}
	rm -rf package
	rm -rf docs

docs :
	doxygen Doxyfile

package :
	make clean;
	mkdir package;
	tar -cvzf package/UCP_Assignment_Tim_Cochrane_17766247.tar.gz * .git\
		--exclude='package' --exclude="dict.txt"
