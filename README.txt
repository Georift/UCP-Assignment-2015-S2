For best reading run "make clean && make docs" the readme is the first
page in the documentation.
/**

\mainpage 

This program will check the spelling of all words inside the input file
and, depending on configuration, decide on a suitable correction to be
made. It will, depending on configuration, automatically update the word
or it will prompt the user to check if the correction is correct.

\section usage Usage:
./spellcheck [FILE TO CHECK]

spellrc Configuration:
autocorrect = (yes|no)      If yes the program will automatically decide
                            if a word should be change.
                            If no the user will be prompted first.

dictionary = [FILENAME]     The dictionary file should contain correctly spelt
                            words, one per line, which the program will use to
                            suggest spelling.

maxcorrection = [EDIT DIST] The maximum allowable difference between
                            a misspelt word and a correction found.
                            (edit distance)   

\section files Files
- spellcheck.c - Starting point for the entire program
- spellcheck.h - Forward declarations and various function includes
- settings.c   - Handles spellrc file operations
- settings.h   - Function prototypes for settings.c
- list.c       - Handles linked list functionality
- list.h       - Prototypes, typedef and defines
- file.c       - Contains functions related to file operations
- file.h       - Function prototypes for file.c
- callback.c   - Contains actionFunc callback functions
- callback.h   - Prototypes for callback functions
- spellrc      - Configuration provided in assignment specification
- Doxyfile     - configuration for doxygen. for documentation run 
                 "make clean; make docs"
- Makefile     - "make clean; make"
- linux.words    (Omitted to keep filesize low)
- dict.test    - A test dictionary I made early on.
- testData/*   - Some test input files
- .git/*       - If you want to see my progress.
- README.txt

\section statement Statement of Completion
To the best of my knowledge all I have completed all of the functionality
listed in the assignment specification and it is working without any known
problems.

\section valgrind Valgrind/Bugs
The only errors which are output by valgrind are suppressed which to my
knowledge is done because they are known errors in common library. This means
that my program appears to be working without having any memory errors.

I am not aware of any bugs currently in this program.

\section testing Testing
This program has been predominately tested on saeshell01p.curtin.edu.au
although it has briefly been tested on several lab machines. No changes to
memory errors or functionality occurred when I moved between machines.

\section include Note about header files
I have purposely gone ahead and specified all the includes a specific file
requires in it's header file even if that file may have been included
previously. This is for a couple reasons:
    - We have header guards to prevent this causing issues
    - All someone needs to include to easily use a specific set of functions 
      is the corresponding header file.

*/
