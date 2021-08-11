#include "berechnung2.h"

int berechnung3(int x){
    if (x < 100000){
        return berechnung2(x, 2 * x, 3 * x);
    }
    return x;
}
