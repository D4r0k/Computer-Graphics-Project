#ifndef CILINDRO_H_INCLUDED
#define CILINDRO_H_INCLUDED
#include "aux.h"
#include "objrevolucion.h"
#include "malla.h"

class Cilindro : public ObjRevolucion {
private:
  float altura;
  float radio;
public:
    Cilindro(int num_vert_perfil, int num_instancias, float h, float r, bool tapa_sup, bool tapa_inf);

};

#endif 
