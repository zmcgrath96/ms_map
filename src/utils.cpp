
/**
 * Used for qsort on floats. If d1 < d2, a number < 0 returned
 * if d1 > d2, a number > 0 returned
 * 
*/
int dblCmp(const void * d1, const void * d2){
    return *(float *)d1 - *(float *)d2;
}

/**
 * Convert the ppm value of a given mass to a value in daltons
 * 
 * @param mass      float  the mass to calculate the dalton tolerance for
 * @param ppmTol    int     the tolerance in ppm
 * 
 * @return float   the tolerance in daltons 
*/
float ppmToDa(float mass, int ppmTol){
    return ((float)ppmTol / 1000000.0) * mass;
}