#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t zufallszahl(uint32_t *zufall){
    /*
     * Anmerkung: Dieser Zufallszahlengenerator generiert nur
     * (vorhersagbare) Pseudozufallszahlen.
     * Eine richtige Lotterie sollte stattdessen ein Verfahren
     * verwenden, das sich nicht vorhersagen lässt.
     */
    uint32_t x = *zufall;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    *zufall = x;
    return x;
}

void wuerfeln(int *zahlen, uint32_t *zufall){
    for (int k = 0; k < 100; k++){
        int i = zufallszahl(zufall) % 100;
        int zahl = zufallszahl(zufall) % 100;

        zahlen[i] = zahl;
    }
}

void sortieren(int *zahlen, int n){
    for (int i = 0; i < n; i++){
        for (int j = 1; j < n; j++){
            if (zahlen[j - 1] > zahlen[j]){
                int x = zahlen[j - 1];
                zahlen[j - 1] = zahlen[j];
                zahlen[j] = x;
            }
        }
    }
}

void ueberpruefen(int *lottozahlen){
    for (int i = 0; i < 6; i++){

        int lottozahl = lottozahlen[i];

        if (lottozahl < 1 || lottozahl > 49){
            printf("FEHLER: Lottozahlen sollen zwischen 1 und 49 liegen.\n");
            printf("Diese Zahl hat aber den den Wert %i\n", lottozahl);
            exit(EXIT_FAILURE);
        }
    }
}

void lottozahlen_wuerfeln(int *lottozahlen, int *zahlen, uint32_t *zufall){
    for (int j = 0; j < 6; j++){
        wuerfeln(zahlen, zufall);

        int x = -26;
        for (int i = 0; i < 50; i++){
            x += zahlen[i] % 2;
        }

        if (x < 0) x = 0;

        x += 1 + zufallszahl(zufall) % 40;

        lottozahlen[j] = x;
    }
}

int main(){
    uint32_t zufall = 24;
    int zahlen[100];
    for (int i = 0; i < 100; i++){
        zahlen[i] = i + 1;
    }

    printf("Die Lottozahlen lauten:\n");

    for (int woche = 1; woche <= 20; woche++){
        int lottozahlen[6];
        lottozahlen_wuerfeln(lottozahlen, zahlen, &zufall);
        sortieren(lottozahlen, 6);
        ueberpruefen(lottozahlen);

        printf("Woche %i: ", woche);
        for (int j = 0; j < 6; j++){
            printf("%i ", lottozahlen[j]);
        }
        printf("\n");
    }
    return 0;
}
