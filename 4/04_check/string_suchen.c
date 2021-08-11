#include <string.h>
#include <stdio.h>

int string_suchen(char *text, char *string){
    int text_laenge = strlen(text);
    int string_laenge = strlen(text);

    // Iteriere über text.
    for (int i = 0; i < text_laenge; i++){

        // Prüfe, ob Zeichen von text an position i mit string übereinstimmen.
        int alle_gleich = 0;
        for (int j = 0; j < string_laenge; j++){
            if (text[i + j] == string[j]){
                alle_gleich = 1;
            }else{
                alle_gleich = 0;
            }
        }

        // Wenn alle Zeichen gleich sind, dann wurde ein Treffer gefunden.
        if (alle_gleich){
            return i;
        }
    }

    // Kein Treffer gefunden, -1 zurückgeben
    return -1;
}
