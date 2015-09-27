typedef struct {
    int maxCorrection;
    char dictionary[30];
    int autoCorrect;
} Settings;

int getSettings(Settings* inSet);

