#include <stdlib.h>
#include <math.h>
#include "cilindro.h"

struct cilindro {
    float altura;
    float raio;
};

Cilindro* create(float x, float y) {
    Cilindro* c = (Cilindro*) malloc(sizeof(Cilindro));
    
    if( c != NULL ) {
        c -> altura = x;
        c -> raio = y;
    }
    return c;
}

void destroy(Cilindro* c) {
    free(c);
}

float getAltura(Cilindro* c) {
    return ( c -> altura );
}

float getRaio(Cilindro* c) {
    return ( c -> raio );
}

float getAreaBase(Cilindro* c){
    float raio = c -> raio;
    return 3.14 * raio * raio;
}

float getAreaLateral(Cilindro* c){
    float altura = c -> altura;
    float raio = c -> raio;
    return 2 * 3.14 * raio * altura;
}

float getAreaTotal(Cilindro* c){
    return 2 * getAreaBase(c) + getAreaLateral(c);
}

float getVolume(Cilindro* c){
    float raio = c -> raio;
    float altura = c -> altura;
    return 3.14 * raio * raio * altura;
}