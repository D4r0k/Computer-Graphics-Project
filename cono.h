#ifndef CONO_H_INCLUDED
#define CONO_H_INCLUDED
#include "aux.h"
#include "objrevolucion.h"
#include "malla.h"

class Cono : public ObjRevolucion {
private:
  float altura;
  float radio;
public:
    Cono(int num_vert_perfil, int num_instancias, float h, float r, bool tapa_sup, bool tapa_inf);

};

#endif 
