#ifndef CUERPO_H_INCLUDED
#define CUERPO_H_INCLUDED
#include "aux.h"
#include "objrevolucion.h"
#include "malla.h"
#include "cubo.h"
#include "cilindro.h"
#include "material.h"

class Cuerpo : public Malla3D
{
    private:
    Cilindro * torso = nullptr;

   public:
   Cuerpo();
   void draw(int opcion, std::vector<bool> edicion, Material *& material,bool hayTapas);
   void drawSimple();
   void aplicarColor(Tupla3f color);
   void aplicarMaterial(Material *& material);

} ;


#endif
