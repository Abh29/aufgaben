#include "berechnung1.h"
#include "berechnung2.h"
#include "berechnung3.h"

#include <stdio.h>

int main(){
    int ergebnis = berechnung1(16, 5) + berechnung2(5, 5, 19);

    printf("%i\n", ergebnis);

    return 0;
}
