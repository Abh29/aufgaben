#include "mathematik.h"
#include "berechnung3.h"

int berechnung1(int x, int y){
    return wurzel(x) + quadrat(y) + berechnung3(quadrat(x));
}
