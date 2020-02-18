#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "semiesfera.h"
#include "ply_reader.h"
#include "luz.h"
#include "luzdireccional.h"
#include "luzposicional.h"
#include "material.h"
#include "habitacion.h"
#include "cabeza.h"
#include "cuerpo.h"
#include "extremidad.h"
#include "robot.h"
#include "muro.h"
#include "textura.h"
#include "cuadro.h"
#include "camara.h"

typedef enum {NADA, SELCAMARA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO,SELILUMINACION,SELOBJETOJERARQUICO, SELANIMACIONAUTO, SELILUAUTO} menu;
class Escena
{

   private:




   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

 
   GLfloat Width, Height, Front_plane, Back_plane;


	void change_projection( const float ratio_xy );
	void change_observer();



   void clear_window();

   menu modoMenu=NADA;

   Ejes ejes;
   Cubo * cubo = nullptr ; 
   Tetraedro * tetraedro= nullptr ; 
   Cilindro * cilindro = nullptr;
   Cilindro * cilindro_sinTapa = nullptr;
   Cono * cono = nullptr;
   Esfera * esfera = nullptr;
   Semiesfera * semiesfera = nullptr;
   Cabeza * cabeza = nullptr;
   Cuerpo * cuerpo = nullptr;
   Robot * robot = nullptr;
   Extremidad * extremidad = nullptr;
   Cuadro * suelo = nullptr;
   Cuadro * ventana = nullptr;

   ObjRevolucion * peon = nullptr;

   int cuboActivado = 0,
       tetraedroActivado = 0;
   int modo_dibujado = 1,
       modo_ajedrez = 0;
    int gradoEscogido;
      std::vector<bool> edicion ={false,false,true,false};

    char angulo_escogido;
    LuzDireccional * luz_0 = nullptr;
    LuzPosicional * luz_1 = nullptr;
    LuzPosicional * luz_2 = nullptr;
    LuzPosicional * luz_3 = nullptr;
    std::vector<bool> lucesActivadas;

    Material * material1;
    Material * material2;
    Material * material3;
    Textura * textura_cuadro;
    Textura * textura_interior;
    Textura * textura_madera;
    Textura * textura_ventana;

    Habitacion * habitacion1;
    Habitacion * habitacion2;
    Habitacion * habitacion3;
    Muro * muro;

    bool hayTapas = true;
    int tapaActivada = 1;

    Camara * camara1 = nullptr;
    Camara * camara2 = nullptr;
    Camara * camara3 = nullptr;
    std::vector<Camara> camarasActivadas;
    int camaraActiva;



    bool btnizqpulsado = false;
    float anteriorX, anteriorY;

    Tupla3f colorSeleccion ={0,0,0};
    Material * materialSeleccion;
    Tupla3f colorRatonEncima ={0,0,0};
    Material * materialRatonEncima;

    std::vector<int> camaraApunta = {-1,-1,-1};
    int objetoSeleccionado;
    float velocidad;
    std::vector<int> modoDibujadoCamara = {-1,-1,-1};

    bool seleccionActiva = false;

   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;


	// Dibujar
	void dibujar() ;
  void dibujarSimple();

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

  void animarModeloJerarquico();
  void animarLuzPuntual();

  void clickRaton(int boton, int estado, float x, float y);
  void ratonMovido(float x, float y);
  int seleccionarObjeto(float x, float y);
  void ratonEncima(float x, float y);

};
#endif
