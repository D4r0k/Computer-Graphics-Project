#include "cuerpo.h"

Cuerpo::Cuerpo(){
    torso = new Cilindro(25,25,40,15,true,true);
    torso->aplicarColor(Tupla3f(1,0,0));
    torso->aplicarColorSeleccion(Tupla3f(0.2,0,0));

}

void Cuerpo::draw(int opcion, std::vector<bool> edicion, Material *& material, bool hayTapas){

    glPushMatrix();
        glTranslatef(0,0,0);
        torso->draw(opcion,edicion,hayTapas);
    glPopMatrix();


}

void Cuerpo::drawSimple(){

    glPushMatrix();
        glTranslatef(0,0,0);
        torso->drawSimple();
    glPopMatrix();


}

void Cuerpo::aplicarColor(Tupla3f color){
  torso->aplicarColor(color);
}

void Cuerpo::aplicarMaterial(Material *& material){
  torso->aplicarMaterial(material);
}
