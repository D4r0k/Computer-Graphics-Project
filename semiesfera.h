#ifndef SEMIESFERA_H_INCLUDED
#define SEMIESFERA_H_INCLUDED
#include "aux.h"
#include "objrevolucion.h"
#include "malla.h"

class Semiesfera : public ObjRevolucion {
private:
  float radio;
public:
    Semiesfera(int num_vert_perfil, int num_instancias,float r);

};

#endif 
