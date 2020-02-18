#include "luzdireccional.h"

LuzDireccional::LuzDireccional(Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso){
    this->posicion = Tupla4f(0,0,1,0);
    id = idLuzOpenGL;
    this->colorAmbiente = colorAmbiente;
    this->colorEspecular = colorEspecular;
    this->colorDifuso = colorDifuso;
}

void LuzDireccional::variarAnguloAlpha(float incremento){

    float x,y,z;

    x = (cos(incremento) * this->posicion(0)) + (sin(incremento) * this->posicion(2));
    y = this->posicion(1);
    z = ((-sin(incremento)) * this->posicion(0)) + (cos(incremento) * this->posicion(2));

    this->posicion = Tupla4f(x,y,z,0);
}

void LuzDireccional::variarAnguloBeta(float incremento){
    float x,y,z;
    x = this->posicion(0);
    y = (cos(incremento) * this->posicion(1)) - (sin(incremento) * this->posicion(2));
    z = (sin(incremento) * this->posicion(1)) + (cos(incremento) * this->posicion(2));

    this->posicion = Tupla4f(x,y,z,0);
}


void LuzDireccional::representar(){
    glLightfv(this->id, GL_POSITION, this->posicion);
    glLightfv(this->id, GL_AMBIENT, this->colorAmbiente);
    glLightfv(this->id, GL_SPECULAR, this->colorEspecular);  
    glLightfv(this->id, GL_DIFFUSE, this->colorDifuso);
     
}