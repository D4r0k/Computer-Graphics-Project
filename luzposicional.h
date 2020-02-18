#ifndef LUZ_POSICIONAL_H
#define LUZ_POSICIONAL_H

#include "luz.h"

class LuzPosicional: public Luz{
    private:
        bool bajarAltura;

    public:
        LuzPosicional(Tupla3f posicion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso);
        void activar();
        void representar();
        void desactivar();
        void animarLuz();        
};

#endif