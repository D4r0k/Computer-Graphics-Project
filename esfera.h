#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED
#include "aux.h"
#include "objrevolucion.h"
#include "malla.h"

class Esfera : public ObjRevolucion {
private:
  float radio;
public:
    Esfera(int num_vert_perfil, int num_instancias,float r);

};

#endif 
