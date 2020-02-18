#ifndef _CAMARA_H
#define _CAMARA_H
#include <iostream>
#include <cmath>
#include "aux.h"

class Camara{

    protected:
	    Tupla3f eye;
	    Tupla3f at;
	    Tupla3f up;
	    int tipo; // ORTOGONAL o Perspectiva
	    float left, right, top, bottom, near, far; 

		Tupla3f vector_n;
		Tupla3f vector_u;
		Tupla3f vector_v;
		float valor_n;
		float valor_u;
		float valor_v;
		float valor_aux;

    public:
      const float PI = 3.14159265;
	    Camara(Tupla3f eye, Tupla3f at, Tupla3f up, int tipo, float left, float right, float top, float bottom, float near, float far) ; // con los parametros necesarios
      void calcularVectores();
	  void calcularEye();
	  void calcularUp();
      void rotarXExaminar(float angle);
	  void rotarYExaminar(float angle);
	  void rotarXPrimeraPersona(float angle);
	  void rotarYPrimeraPersona(float angle);
	  void zoom(float factor) ;
      void setObserver();
      void setProyeccion();
      void setObjetivo(float x, float y, float z);
};


#endif
