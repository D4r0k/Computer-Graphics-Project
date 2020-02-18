#ifndef _TEXTURA_H
#define _TEXTURA_H

#include "jpg_imagen.hpp"
#include "tuplasg.h"
#include "aux.h"
#include <vector>

class Textura{
    private:
        GLuint textura_id = 0;
        unsigned char * texels;
        int width,height;
    public:
        Textura(std::string archivo);
        void activar();
};

#endif