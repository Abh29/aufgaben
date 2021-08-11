#include "mathematik.h"

#include <stdint.h>

int quadrat(int x){
    // Berechnet das Quadrat einer Zahl x
    return x * x;
}

int anzahl_bits(int x){
    for (int bit_position = 30; bit_position >= 0; bit_position--){
        int bit = 1 << bit_position;

        if (bit & x){
            return bit_position + 1;
        }
    }

    return 0;
}

int wurzel(int x){
    // Berechnet die Wurzel einer Zahl x zwischen 0 und 0x3FFFFFFF
    int bit = anzahl_bits(x);

    if (bit & 1){
        bit ^= 1;
    }

    int result = 0;

    for (; bit >= 0; bit -= 2){
        int tmp = result | (1 << bit);

        if (x >= tmp){
            x -= tmp;
            result |= 1 << (bit + 1);
        }
        result >>= 1;
    }
    return result;
}
