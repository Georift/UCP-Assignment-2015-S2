CC = gcc
CFLAG = -Wall -pedantic -ansi
OBJ = spellcheck.o check.o settings.o
EXEC = spellcheck

all : ${EXEC}
debug : CFLAG += -g -DDEBUG
debug : ${EXEC}

${EXEC} : ${OBJ}
	${CC} ${CFLAG} ${OBJ} -o ${EXEC}

spellcheck.o : spellcheck.h settings.h check.h
	${CC} ${CFLAG} -c spellcheck.c

settings.c : settings.h spellcheck.h
	${CC} ${CFLAG} -c settings.c

check.o : check.h
	${CC} ${CFLAG} -c check.c

clean :
	rm -rf spellcheck ${OBJ}
	rm -rf package
	rm -rf docs

docs :
	doxygen Doxyfile
	google-chrome docs/html/index.html

submission :
	mkdir package;
	tar -cvzf package/submission.tar.gz * .git* --exclude='package'
