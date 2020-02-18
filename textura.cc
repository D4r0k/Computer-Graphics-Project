#include "textura.h"
#include "jpg_imagen.hpp"

Textura::Textura(std::string archivo){
    jpg::Imagen * pimg = NULL;

    pimg = new jpg::Imagen(archivo);

    width = pimg->tamX();
    height = pimg->tamY();

    texels = pimg->leerPixels();

    glGenTextures(1, &textura_id);
    glBindTexture(GL_TEXTURE_2D, textura_id);
}

void Textura::activar(){
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, texels);
}