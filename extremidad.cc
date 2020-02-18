#include "extremidad.h"

Extremidad::Extremidad(){
  brazo = new Cilindro(25,25,14,3,true,true);
    brazo->aplicarColor(Tupla3f(1,0,1));
    brazo->aplicarColorSeleccion(Tupla3f(0.2,0,0));
    hombro  = new Esfera(25,25,5);
    hombro->aplicarColor(Tupla3f(1,1,0));
    hombro->aplicarColorSeleccion(Tupla3f(0.2,0,0));

}

void Extremidad::draw(int opcion, std::vector<bool> edicion, Material *& material, bool hayTapas){

    glPushMatrix();
        glTranslatef(0,0,0);
        hombro->draw(opcion,edicion,hayTapas);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,-17,0);
        brazo->draw(opcion,edicion,hayTapas);
    glPopMatrix();
}

void Extremidad::drawSimple(){

    glPushMatrix();
        glTranslatef(0,0,0);
        hombro->drawSimple();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,-17,0);
        brazo->drawSimple();
    glPopMatrix();
}

void Extremidad::aplicarColor(Tupla3f color){
  hombro->aplicarColor(color);
  brazo->aplicarColor(color);
}

void Extremidad::aplicarMaterial(Material *& material){
  hombro->aplicarMaterial(material);
  brazo->aplicarMaterial(material);
}
