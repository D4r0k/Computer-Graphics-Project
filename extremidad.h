#ifndef EXTREMIDAD_H_INCLUDED
#define EXTREMIDAD_H_INCLUDED
#include "aux.h"
#include "objrevolucion.h"
#include "malla.h"
#include "esfera.h"
#include "cilindro.h"
#include "material.h"
class Extremidad : public Malla3D
{
    private:
    Esfera * hombro = nullptr;
    Cilindro * brazo = nullptr;

   public:
   Extremidad();
   void draw(int opcion, std::vector<bool> edicion, Material *& material, bool hayTapas);
   void drawSimple();
   void aplicarColor(Tupla3f color);
   void aplicarMaterial(Material *& material);

} ;


#endif
