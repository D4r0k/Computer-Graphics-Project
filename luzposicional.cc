#include "luzposicional.h"

LuzPosicional::LuzPosicional(Tupla3f posicion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso){
    this->posicion = Tupla4f(posicion(0), posicion(1), posicion(2), 1);
    this->id = idLuzOpenGL;
    this->colorAmbiente = colorAmbiente;
    this->colorEspecular = colorEspecular;
    this->colorDifuso = colorDifuso;
        this->bajarAltura = true;
}

void LuzPosicional::activar(){
    glEnable(this->id);
}

void LuzPosicional::desactivar(){
    glDisable(this->id);
}

void LuzPosicional::representar(){
    glLightfv(this->id, GL_AMBIENT, this->colorAmbiente);
    glLightfv(this->id, GL_DIFFUSE, this->colorDifuso);
    glLightfv(this->id, GL_SPECULAR, this->colorEspecular);
    glLightfv(this->id, GL_POSITION, this->posicion);
}

void LuzPosicional::animarLuz(){
    if(this->posicion(2) == 425){
        bajarAltura = true;
    }

    if(this->posicion(2) == 0){
        bajarAltura = false;
    }

    if(bajarAltura){
        this->posicion(2)= this->posicion(2) - 5;

    }else{
        this->posicion(2)= this->posicion(2) + 5;

    }

}
