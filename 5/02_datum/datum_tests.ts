#include "datum.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void datum_pruefen(int jahr, int monat, int tag, char *erwartet){
    // Dieser Test schreibt ein Datum in eine Datei, um es danach
    // auszulesen und zu vergleichen.

    // Zufälligen Dateinamen generieren, damit niemand versucht, die
    // Datei selber zu öffnen.
    char dateiname[100];
    snprintf(dateiname, sizeof(dateiname), "datum_%i.txt", rand());

    // Datei öffnen.
    FILE *datei = fopen(dateiname, "w");
    // Datum erstellen.
    struct datum ein_datum;
    datum_setzen(&ein_datum, jahr, monat, tag);

    // Datum in eine Datei schreiben.
    datum_ausgeben(datei, &ein_datum);

    // Prüfen, ob Datei von Student geschlossen wurde.
    int error = fseek(datei, 0, SEEK_SET);
    if (error){
        printf(
            "FEHLER: Die Datei darf nicht geschlossen werden. "
            "Wahrscheinlich will der Benutzer der Funktion noch mehr "
            "in die Datei schreiben, als nur ein Datum. Das aufrufende "
            "Programm schliesst die Datei bereits. Eine Datei darf "
            "nicht doppelt geschlossen werden.\n"
        );
        remove(dateiname);
        exit(1);
    }
    fclose(datei);

    // Datum aus Datei lesen und vergleichen.
    datei = fopen(dateiname, "r");

    // Null-Initialisierten Speicher anlegen.
    char datum_text[100 + 1];
    memset(datum_text, 0, sizeof(datum_text));

    // Bis zu 100 Zeichen lesen
    int n = fread(datum_text, 1, 100, datei);

    // Aufräumen.
    fclose(datei);
    remove(dateiname);

    if (n >= 0){
        printf("Ausgegebenes datum: \"%s\"\n", datum_text);
    }

    if (n != 10){
        printf("FEHLER: Datum muss genau 10 Zeichen lang sein\n");
    }
    ck_assert_int_eq(n, 10);

    ck_assert_str_eq(datum_text, erwartet);
}

#test datum_ist_gleich
    struct datum a, b;
    datum_setzen(&a, 2020, 12, 24);
    datum_setzen(&b, 2020, 12, 24);
    ck_assert_int_eq(datum_vergleichen(&a, &b), 0);
    ck_assert_int_eq(datum_vergleichen(&b, &a), 0);

#test datum_ist_davor
    struct datum a, b;
    datum_setzen(&a, 2019, 11, 1);
    datum_setzen(&b, 2020, 12, 2);
    ck_assert_int_lt(datum_vergleichen(&a, &b), 0);
    ck_assert_int_gt(datum_vergleichen(&b, &a), 0);

#test datum_ist_danach
    struct datum a, b;
    datum_setzen(&a, 2020, 12, 1);
    datum_setzen(&b, 2020, 11, 1);
    ck_assert_int_gt(datum_vergleichen(&a, &b), 0);
    ck_assert_int_lt(datum_vergleichen(&b, &a), 0);

#test datum_ist_davor_gleiches_jahr
    struct datum a, b;
    datum_setzen(&a, 2020, 1, 30);
    datum_setzen(&b, 2020, 2, 30);
    ck_assert_int_lt(datum_vergleichen(&a, &b), 0);
    ck_assert_int_gt(datum_vergleichen(&b, &a), 0);

#test datum_ist_davor_gleicher_monat_gleicher_tag
    struct datum a, b;
    datum_setzen(&a, 2019, 1, 30);
    datum_setzen(&b, 2020, 1, 30);
    ck_assert_int_lt(datum_vergleichen(&a, &b), 0);
    ck_assert_int_gt(datum_vergleichen(&b, &a), 0);

#test datum_ist_davor_gleicher_monat_gleiches_jahr
    struct datum a, b;
    datum_setzen(&a, 2020, 8, 30);
    datum_setzen(&b, 2020, 8, 31);
    ck_assert_int_lt(datum_vergleichen(&a, &b), 0);
    ck_assert_int_gt(datum_vergleichen(&b, &a), 0);

#test datum_ist_danach_gleicher_monat_gleiches_jahr
    struct datum a, b;
    datum_setzen(&a, 100, 12, 30);
    datum_setzen(&b, 100, 12, 29);
    ck_assert_int_lt(datum_vergleichen(&b, &a), 0);
    ck_assert_int_gt(datum_vergleichen(&a, &b), 0);

#test datum_ausgabe_zweistellig
    datum_pruefen(2020, 12, 30, "2020-12-30");

#test datum_ausgabe_einstelliger_monat_und_tag
    datum_pruefen(1970, 1, 1, "1970-01-01");

#test datum_ausgabe_einstelliges_jahr
    datum_pruefen(1, 10, 20, "0001-10-20");

#test datum_ausgabe_zweistelliges_jahr
    datum_pruefen(99, 10, 1, "0099-10-01");

#test datum_ausgabe_dreistelliges_jahr
    datum_pruefen(123, 3, 14, "0123-03-14");
