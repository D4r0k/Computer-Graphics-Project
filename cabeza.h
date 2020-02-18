#ifndef CABEZA_H_INCLUDED
#define CABEZA_H_INCLUDED
#include "aux.h"
#include "objrevolucion.h"
#include "malla.h"
#include "semiesfera.h"
#include "esfera.h"
#include "cilindro.h"
#include "tetraedro.h"
#include "material.h"

class Cabeza : public Malla3D
{
    private:
    Semiesfera * semiesfera = nullptr;
    Cilindro * cuello = nullptr;
    Esfera * ojo1 = nullptr;
    Esfera * ojo2 = nullptr;
    Tetraedro * oreja1 = nullptr;
    Tetraedro * oreja2 = nullptr;

   public:
   Cabeza();
   void draw(int opcion, std::vector<bool> edicion, Material *& material, bool hayTapas);
   void drawSimple();
   void aplicarColor(Tupla3f color);
   void aplicarMaterial(Material *& material);

} ;


#endif
