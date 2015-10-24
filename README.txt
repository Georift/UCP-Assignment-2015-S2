UCP Assignment - Tim Cochrane (17766247)

Usage:
./spellcheck [FILE TO CHECK]

This program will check the spelling of all words inside the input file
and, depending on configuration, decide on a suitable correction to be
made. It will, depending on configuration, automatically update the word
or it will prompt the user to check if the correction is correct.

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
