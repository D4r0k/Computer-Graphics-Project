#ifndef MATERIAL_H
#define MATERIAL_H

#include "aux.h"
#include "tuplasg.h"

class Material{
    private:
        Tupla4f difuso;
        Tupla4f especular;
        Tupla4f ambiente;
        float brillo;

    public:
        Material(Tupla4f ambiente, Tupla4f difuso, Tupla4f especular, float brillo);
        void aplicar();
};

#endif