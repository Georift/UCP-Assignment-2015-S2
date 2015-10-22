/**
 * \brief used to store the spellrc configuration
 */
typedef struct {
    /** Integer value of max difference for acceptable correction */
    int maxCorrection;
    /** Name of the dictionary file to use */
    char dictionary[30];
    /** Boolean for if the program should auto correct. 1=yes 0=no */
    int autoCorrect;
} Settings;

int getSettings(Settings* inSet);

