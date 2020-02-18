#include "luz.h"

Luz::Luz(){}

void Luz::activar(){
    glEnable(this->id);
}

void Luz::desactivar(){
    glDisable(this->id);
}

