#include <stdio.h>
#include "cilindro.h"

int main()
{   
    Cilindro* c = create(4, 9);
    
    printf("Altura: %.2f \n", getAltura(c));
    printf("Raio: %.2f \n", getRaio(c));
    printf("Area da base: %.2f \n", getAreaBase(c));
    printf("Area Lateral: %.2f \n", getAreaLateral(c));
    printf("Area total: %.2f \n", getAreaTotal(c));
    printf("Volume: %.2f \n", getVolume(c));
    
    destroy(c);
    
    return 0;
}