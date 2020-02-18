#include "robot.h"

Robot::Robot(){

    cabeza = new Cabeza();
    cuerpo = new Cuerpo();
    brazoIzq = new Extremidad();
    brazoDer = new Extremidad();
    piernaIzq = new Extremidad();
    piernaDer = new Extremidad();
    alturaCabeza = 40;
    anguloCabezaY = 0;
    anguloBrazoIzqX = 0;
    anguloBrazoIzqZ = 0;
    anguloBrazoDerX = 0;
    anguloBrazoDerZ = 0;
    anguloPiernaIzqX = 0;
    anguloPiernaDerX = 0;
}

void Robot::draw(int opcion, std::vector<bool> edicion, Material *& material, bool hayTapas){
glMatrixMode(GL_MODELVIEW);
glPushMatrix();
    glPushMatrix();
        glTranslatef(0,alturaCabeza,0);
        glPushMatrix();
            glRotatef(anguloCabezaY,0,1,0);
            glScalef(1.2,1.2,1.2);
            cabeza->draw(opcion,edicion,material,hayTapas);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,20,0);
        cuerpo->draw(opcion,edicion,material,hayTapas);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-19,52,0);
        glPushMatrix();
            glRotatef(anguloBrazoIzqX,1,0,0);
            glPushMatrix();
                glRotatef(anguloBrazoIzqZ,0,0,1);
                brazoIzq->draw(opcion,edicion,material,hayTapas);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(19,52,0);
       glPushMatrix();
            glRotatef(anguloBrazoDerX,1,0,0);
            glPushMatrix();
                glRotatef(anguloBrazoDerZ,0,0,1);
                brazoDer->draw(opcion,edicion,material,hayTapas);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-7,17,0);
        glPushMatrix();
        glRotatef(anguloPiernaIzqX,1,0,0);
        piernaIzq->draw(opcion,edicion,material,hayTapas);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(7,17,0);
        glPushMatrix();
        glRotatef(anguloPiernaDerX,1,0,0);
        piernaDer->draw(opcion,edicion,material,hayTapas);
        glPopMatrix();
    glPopMatrix();
glPopMatrix();
}

void Robot::cambiarAlturaCabeza(float incremento){
    if((alturaCabeza+incremento) >= 40 && (alturaCabeza+incremento) <= 60)
        alturaCabeza += incremento;
}

void Robot::cambiarAnguloCabezaY(float incremento){
    if((anguloCabezaY+incremento)>=-30 && (anguloCabezaY+incremento) <= 30)
        anguloCabezaY += incremento;
}

void Robot::cambiarAnguloBrazoIzqX(float incremento){
    if((anguloBrazoIzqX+incremento)>=-50 && (anguloBrazoIzqX+incremento) <= 50)
        anguloBrazoIzqX += incremento;
}

void Robot::cambiarAnguloBrazoIzqZ(float incremento){
    if((anguloBrazoIzqZ+incremento)<=0 && (anguloBrazoIzqZ+incremento) >= -90)
        anguloBrazoIzqZ += incremento;
}

void Robot::cambiarAnguloBrazoDerX(float incremento){
    if((anguloBrazoDerX+incremento)>=-50 && (anguloBrazoDerX+incremento) <= 50)
        anguloBrazoDerX += incremento;
}

void Robot::cambiarAnguloBrazoDerZ(float incremento){
    if((anguloBrazoDerZ+incremento)>=0 && (anguloBrazoDerZ+incremento) <= 90)
        anguloBrazoDerZ += incremento;
}

void Robot::cambiarAnguloPiernaIzqX(float incremento){
    if((anguloPiernaIzqX+incremento)>=-50 && (anguloPiernaIzqX+incremento) <= 50)
        anguloPiernaIzqX += incremento;
}

void Robot::cambiarAnguloPiernaDerX(float incremento){
    if((anguloPiernaDerX+incremento)>-50 && (anguloPiernaDerX+incremento) < 50)
        anguloPiernaDerX += incremento;
}

void Robot::animarRobot(float velocidad){

    if(velocidad >= 0){
        if(anguloPiernaDerX+velocidad > 50){
            subirExtremidad = false;
        }else if(anguloPiernaDerX+velocidad < -50){
            subirExtremidad = true;
        }

        if(alturaCabeza+velocidad > 60){
            subirCabeza = false;
        }else if(alturaCabeza+velocidad < 40){
            subirCabeza = true;
        }

        if(anguloCabezaY+velocidad > 30){
            girarCabeza = false;
        }else if(anguloCabezaY+velocidad < -30){
            girarCabeza = true;
        }

        if(girarCabeza){
            anguloCabezaY += velocidad/2;
        }else{
            anguloCabezaY -= velocidad/2;
        }

        if(subirCabeza){
            alturaCabeza += velocidad/4;
        }else{
            alturaCabeza -= velocidad/4;
        }

        if(subirExtremidad){
            anguloPiernaDerX += velocidad;
            anguloBrazoIzqX += velocidad;
            anguloPiernaIzqX -= velocidad;
            anguloBrazoDerX -= velocidad;

        }else{
            anguloPiernaDerX -= velocidad;
            anguloBrazoIzqX -= velocidad;
            anguloPiernaIzqX += velocidad;
            anguloBrazoDerX += velocidad;

        }
    }

}

void Robot::drawSimple(){

glPushMatrix();
    glPushMatrix();
        glTranslatef(0,alturaCabeza,0);
        glPushMatrix();
            glRotatef(anguloCabezaY,0,1,0);
            glScalef(1.2,1.2,1.2);
            cabeza->drawSimple();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,20,0);
        cuerpo->drawSimple();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-19,52,0);
        glPushMatrix();
            glRotatef(anguloBrazoIzqX,1,0,0);
            glPushMatrix();
                glRotatef(anguloBrazoIzqZ,0,0,1);
                brazoIzq->drawSimple();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(19,52,0);
       glPushMatrix();
            glRotatef(anguloBrazoDerX,1,0,0);
            glPushMatrix();
                glRotatef(anguloBrazoDerZ,0,0,1);
                brazoDer->drawSimple();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-7,17,0);
        glPushMatrix();
        glRotatef(anguloPiernaIzqX,1,0,0);
        piernaIzq->drawSimple();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(7,17,0);
        glPushMatrix();
        glRotatef(anguloPiernaDerX,1,0,0);
        piernaDer->drawSimple();
        glPopMatrix();
    glPopMatrix();
glPopMatrix();
}

void Robot::aplicarColor(Tupla3f color){
  cabeza->aplicarColor(color);
  cuerpo->aplicarColor(color);
  brazoIzq->aplicarColor(color);
  brazoDer->aplicarColor(color);
  piernaIzq->aplicarColor(color);
  piernaDer->aplicarColor(color);
}

void Robot::aplicarMaterialTotal(Material *& material){
  cabeza->aplicarMaterial(material);
  cuerpo->aplicarMaterial(material);
  brazoIzq->aplicarMaterial(material);
  brazoDer->aplicarMaterial(material);
  piernaIzq->aplicarMaterial(material);
  piernaDer->aplicarMaterial(material);
}
