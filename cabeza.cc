#include "cabeza.h"

Cabeza::Cabeza(){
    semiesfera = new Semiesfera(25,25,15);
    semiesfera->aplicarColor(Tupla3f(1,1,0));
    semiesfera->aplicarColorSeleccion(Tupla3f(0.2,0,0));
    cuello = new Cilindro(25,25,20,7,true,true);
    cuello->aplicarColor(Tupla3f(1,1,0));
    cuello->aplicarColorSeleccion(Tupla3f(0.2,0,0));
    ojo1 = new Esfera(25,25,2);
    ojo1->aplicarColor(Tupla3f(0,0,1));
    ojo1->aplicarColorSeleccion(Tupla3f(0.2,0,0));
    ojo2 = new Esfera(25,25,2);
    ojo2->aplicarColor(Tupla3f(0,0,1));
    ojo2->aplicarColorSeleccion(Tupla3f(0.2,0,0));
    oreja1 = new Tetraedro();
    oreja1->aplicarColor(Tupla3f(0,0,1));
    oreja1->aplicarColorSeleccion(Tupla3f(0.2,0,0));
    oreja2 = new Tetraedro();
    oreja2->aplicarColor(Tupla3f(0,0,1));
    oreja2->aplicarColorSeleccion(Tupla3f(0.2,0,0));
}

void Cabeza::draw(int opcion, std::vector<bool> edicion, Material *& material, bool hayTapas){

    glPushMatrix();
        glTranslatef(0,20,0);
        semiesfera->draw(opcion,edicion,hayTapas);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-4,23,13);
        ojo1->draw(opcion,edicion,hayTapas);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(4,23,13);
        ojo2->draw(opcion,edicion,hayTapas);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,0,0);
        cuello->draw(opcion,edicion,hayTapas);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4,30,3);
    glPushMatrix();
        glScalef(0.3,0.3,0.3);
        oreja1->draw(opcion,edicion);
    glPopMatrix();
glPopMatrix();

glPushMatrix();
    glTranslatef(-8,30,3);
    glPushMatrix();
        glScalef(0.3,0.3,0.3);
        oreja2->draw(opcion,edicion);
    glPopMatrix();
glPopMatrix();



}

void Cabeza::drawSimple(){

    glPushMatrix();
        glTranslatef(0,20,0);
        semiesfera->drawSimple();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-4,23,13);
        ojo1->drawSimple();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(4,23,13);
        ojo2->drawSimple();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,0,0);
        cuello->drawSimple();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4,30,3);
    glPushMatrix();
        oreja1->drawSimple();
    glPopMatrix();
glPopMatrix();

glPushMatrix();
    glTranslatef(-8,30,3);
    glPushMatrix();
        glScalef(0.3,0.3,0.3);
        oreja2->drawSimple();
        glPopMatrix();
glPopMatrix();


}

void Cabeza::aplicarColor(Tupla3f color){
  semiesfera->aplicarColor(color);
  cuello->aplicarColor(color);
  ojo1->aplicarColor(color);
  ojo2->aplicarColor(color);
  oreja1->aplicarColor(color);
  oreja2->aplicarColor(color);
}

void Cabeza::aplicarMaterial(Material *& material){
  semiesfera->aplicarMaterial(material);
  cuello->aplicarMaterial(material);
  ojo1->aplicarMaterial(material);
  ojo2->aplicarMaterial(material);
  oreja1->aplicarMaterial(material);
  oreja2->aplicarMaterial(material);
}
