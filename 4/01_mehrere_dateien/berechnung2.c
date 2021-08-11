#include "mathematik.h"
#include "berechnung1.h"

int berechnung2(int x, int y, int z){
    return wurzel(x * y) + z + berechnung1(y, z);
}
