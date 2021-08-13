#include "fahrzeuge.h"

#include <string.h>

void neustes_fahrzeug_finden(struct fahrzeug *neustes, FILE *eingabe){
    /* Implementieren Sie diese Funktion. */





}

char* modell_enum_zu_string(enum fahrzeug_model modell){
    switch (modell){
        case BUS:
            return "Bus";
        case KLEINWAGEN:
            return "Kleinwagen";
        case KOMBI:
            return "Kombi";
        case MOTORRAD:
            return "Motorrad";
        default:
            return "Unbekannt";
    }
}

void fahrzeug_ausgeben(FILE *ausgabe, struct fahrzeug *fahrzeug){
    datum_ausgeben(ausgabe, &fahrzeug->baudatum);

    char *modell = modell_enum_zu_string(fahrzeug->modell);

    fprintf(ausgabe, " %s %s\n", modell, fahrzeug->hersteller);
}

int main(int argc, char **argv){
    /* Diese Funktion darf nicht verändert werden! */

    FILE *eingabe = fopen(argv[1], "r");
    FILE *ausgabe = fopen(argv[2], "w");

    struct fahrzeug neustes;

    neustes_fahrzeug_finden(&neustes, eingabe);

    fahrzeug_ausgeben(ausgabe, &neustes);

    fclose(eingabe);
    fclose(ausgabe);

    return 0;
}
