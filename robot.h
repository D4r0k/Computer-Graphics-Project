#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED
#include "aux.h"
#include "extremidad.h"
#include "cabeza.h"
#include "cuerpo.h"
#include "malla.h"

class Robot : public Malla3D
{
    private:
    Cabeza * cabeza = nullptr;
    Cuerpo * cuerpo = nullptr;
    Extremidad * brazoIzq = nullptr;
    Extremidad * brazoDer = nullptr;
    Extremidad * piernaIzq = nullptr;
    Extremidad * piernaDer = nullptr;

    float alturaCabeza;
    float anguloCabezaY;
    float anguloBrazoIzqX;
    float anguloBrazoIzqZ;
    float anguloBrazoDerX;
    float anguloBrazoDerZ;
    float anguloPiernaIzqX;
    float anguloPiernaDerX;
    bool subirExtremidad;
    bool subirCabeza;
    bool girarCabeza;

   public:
    Robot();
    void draw(int opcion, std::vector<bool> edicion, Material *& material, bool hayTapas);
    void drawSimple();
    void cambiarAlturaCabeza(float incremento);
    void cambiarAnguloCabezaY(float incremento);
    void cambiarAnguloBrazoIzqX(float incremento);
    void cambiarAnguloBrazoIzqZ(float incremento);
    void cambiarAnguloBrazoDerX(float incremento);
    void cambiarAnguloBrazoDerZ(float incremento);
    void cambiarAnguloPiernaIzqX(float incremento);
    void cambiarAnguloPiernaDerX(float incremento);
    void animarRobot(float velocidad);
    void aplicarColor(Tupla3f color);
    void aplicarMaterialTotal(Material *& material);
} ;


#endif
