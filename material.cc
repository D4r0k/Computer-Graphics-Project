#include "material.h"

Material::Material(Tupla4f ambiente, Tupla4f difuso, Tupla4f especular, float brillo){
    this->ambiente = ambiente;
    this->difuso = difuso;
    this->especular = especular;
    this->brillo = brillo;
}

void Material::aplicar(){
    glMaterialfv(GL_FRONT, GL_AMBIENT, this->ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, this->difuso);
    glMaterialfv(GL_FRONT, GL_SPECULAR, this->especular);
    glMaterialf(GL_FRONT, GL_SHININESS, this->brillo);
}