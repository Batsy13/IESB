typedef struct cilindro Cilindro;

Cilindro* create (float, float);

void destroy (Cilindro*);

float getAltura (Cilindro*);

float getRaio (Cilindro*);

float getAreaBase (Cilindro*);

float getAreaLateral (Cilindro*);

float getAreaTotal (Cilindro*);

float getVolume (Cilindro*);