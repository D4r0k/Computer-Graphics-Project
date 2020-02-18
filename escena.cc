

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "semiesfera.h"
#include "luz.h"
#include "luzdireccional.h"
#include "luzposicional.h"
#include "material.h"
#include "cabeza.h"
#include "cuerpo.h"
#include "extremidad.h"
#include "robot.h"
#include "textura.h"
#include "cuadro.h"
#include "camara.h"

#include "habitacion.h"
#include "muro.h"


Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    cubo = new Cubo(25);
    tetraedro = new Tetraedro();
    peon = new ObjRevolucion("./plys/peon.ply", 25, true, true);
    cono = new Cono(25, 25, 25, 10,true,true);
    cilindro = new Cilindro(25, 25, 25, 10,true,true);
    cilindro_sinTapa = new Cilindro(25, 25, 25, 10,false,false);
    esfera = new Esfera(25, 25, 10);
    semiesfera = new Semiesfera(25,25,10);
    cabeza = new Cabeza();
    cuerpo = new Cuerpo();
    extremidad = new Extremidad();
    robot = new Robot();

    luz_0 = new LuzDireccional(Tupla2f(0, 0), GL_LIGHT0, Tupla4f(1, 1, 1, 1), Tupla4f(1, 1, 1, 1), Tupla4f(0, 0, 0, 1));
    luz_1 = new LuzPosicional(Tupla3f(80,100,85), GL_LIGHT1, Tupla4f(0, 0, 0, 0), Tupla4f(1, 1, 1, 1), Tupla4f(1, 1, 1, 1));
    luz_2 = new LuzPosicional(Tupla3f(80,100,255), GL_LIGHT2, Tupla4f(0, 0, 0, 0), Tupla4f(1, 1, 1, 1), Tupla4f(1, 1, 1, 1));
    luz_3 = new LuzPosicional(Tupla3f(80,100,425), GL_LIGHT3, Tupla4f(0, 0, 0, 0), Tupla4f(1, 1, 1, 1), Tupla4f(0, 0, 0, 1));

    lucesActivadas.push_back(false);
    lucesActivadas.push_back(false);
    lucesActivadas.push_back(false);

    material1 = new Material(Tupla4f(0.05, 0.05, 0.05, 1), Tupla4f(0.5, 0.5, 0.5, 1), Tupla4f(0.5, 0.5, 0.5, 1), 0.078125);
    material2 = new Material(Tupla4f(0.0, 0.05, 0.05, 1), Tupla4f(0.4, 0.5, 0.5, 1), Tupla4f(0.04, 0.7, 0.7, 1),0.078125);
    material3 = new Material(Tupla4f(0.0, 0.0, 0.0, 1),Tupla4f(0.0,0.1,1,1.0),Tupla4f(0.0,0.0,0.0,1.0),32.0);

    habitacion1 = new Habitacion();
    habitacion2 = new Habitacion();
    habitacion3 = new Habitacion();

    muro = new Muro();

    Camara * camara1 = new Camara({300, 500, 400}, {0, 0, 0}, {0, 1, 0}, 0,-50, 50,50, -50,35,Back_plane) ;
    Camara * camara2 = new Camara({200, 50, 50}, {0, 0, 0}, {0, 1, 0}, 0,-100,100,100,-100,35,Back_plane) ;
    Camara * camara3 = new Camara({0, 7, 5}, {0, 0, 0}, {0, 1, 0}, 1,-300, 300,300, -300,-500,Back_plane) ;
    camarasActivadas.push_back(*camara1);
    camarasActivadas.push_back(*camara2);
    camarasActivadas.push_back(*camara3);
    camaraActiva = 0 ;

    textura_interior = new Textura("./img/interior.jpg");
    textura_cuadro = new Textura("./img/cuadro.jpg");
    textura_madera = new Textura("./img/text-madera.jpg");
    textura_ventana = new Textura("./img/ventana.jpg");

    ventana = new Cuadro();
    suelo = new Cuadro();

    anteriorX = 0;
    anteriorY = 0;

    colorSeleccion = {0.98431372549, 0.51764705882, 1};
    materialSeleccion = new Material(Tupla4f(0.19125, 0.0735	, 0.0225, 1),Tupla4f(0.7038,0.27048,0.0828,1.0),Tupla4f(0.256777,0.137622,0.086014,1.0),0.1);

    colorRatonEncima = {0.0, 0.50, 1};
    materialRatonEncima = new Material(Tupla4f(0.0, 0.0	, 0.0, 1),Tupla4f(0.5,0.0,0.0,1.0),Tupla4f(0.7,0.6,0.6,1.0),0.25);

    cubo->aplicarMaterial(material3);
    cubo->aplicarColor(Tupla3f(0,0,1));
    cubo->aplicarColorSeleccion(Tupla3f(0,0,1));

    tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
    tetraedro->aplicarColorSeleccion(Tupla3f(0.2,0.2,0));
    tetraedro->aplicarMaterial(material2);

    peon->aplicarColor(Tupla3f(0,1,0));
    peon->aplicarColorSeleccion(Tupla3f(0,1,0));
    peon->aplicarMaterial(material1);

    cono->aplicarColor(Tupla3f(0,1,0));
    cono->aplicarColorSeleccion(Tupla3f(1,0,0));
    cono->aplicarMaterial(material2);

    cilindro->aplicarColor(Tupla3f(0,1,0));
    cilindro->aplicarColorSeleccion(Tupla3f(1,1,0));
    cilindro->aplicarMaterial(material3);

    esfera->aplicarColor(Tupla3f(0,1,0));
    esfera->aplicarColorSeleccion(Tupla3f(1,0,1));
    esfera->aplicarMaterial(material3);

    muro->aplicarColor(Tupla3f(0,1,1));
    muro->aplicarColorSeleccion(Tupla3f(0,1,1));
    muro->aplicarTextura(textura_interior);
    muro->aplicarMaterial(material1);

    ventana->aplicarColor(Tupla3f(0,0.2,0));
    ventana->aplicarColorSeleccion(Tupla3f(0,0.2,0));
    ventana->aplicarTextura(textura_ventana);
    ventana->aplicarMaterial(material1);

    suelo->aplicarColor(Tupla3f(0,0,0.2));
    suelo->aplicarColorSeleccion(Tupla3f(0,0,0.2));
    suelo->aplicarTextura(textura_madera);
    suelo->aplicarMaterial(material1);

    robot->aplicarColor(Tupla3f(0,1,0));
    robot->aplicarColorSeleccion(Tupla3f(0.2,0,0));
    robot->aplicarMaterialTotal(material1);

}



void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );

	glEnable( GL_DEPTH_TEST );	
  glEnable(GL_NORMALIZE);
	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );


}

void Escena::dibujar()
{
  using namespace std;

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 
	change_observer();
  glDisable(GL_LIGHTING);

    ejes.draw();

  glEnable(GL_CULL_FACE);

    if(edicion[3]){
      glEnable(GL_LIGHTING);
      glShadeModel(GL_SMOOTH);
      edicion[0] = false;
      edicion[1] = false;
      edicion[2] = false;
      modo_ajedrez=0;
    }

    if(lucesActivadas[0]){
      luz_0->activar();
      luz_0->representar();
    }else{
      luz_0->desactivar();
    }

    if(lucesActivadas[1]){
      luz_1->activar();
      luz_1->representar();
    }else{
      luz_1->desactivar();
    }

    if(lucesActivadas[2]){
      luz_2->activar();
      luz_2->representar();
    }else{
      luz_2->desactivar();
    }

    if(lucesActivadas[3]){
      luz_3->activar();
      luz_3->representar();
    }else{
      luz_3->desactivar();
    }


    if(modo_ajedrez == 1){
      modo_dibujado = 3;
    }else{
      modo_dibujado = 1;
    }


///////////////////////// INTERIOR ////////////////////////////////////

  muro->draw(modo_dibujado, edicion);

  glPushMatrix();
    glTranslatef(0.0,0.0,160.0);
    glRotatef(90,0,1.0,0);
      muro->draw(modo_dibujado, edicion);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(159.0,0.0,160.0);
    glRotatef(180,0,1.0,0);
      muro->draw(modo_dibujado, edicion);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(160.0,0.0,0.0);
    glRotatef(270,0,1.0,0);
      muro->draw(modo_dibujado, edicion);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.0,0.0,160.0);
      muro->draw(modo_dibujado, edicion);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.0,0.0,320.0);
    glRotatef(90,0,1.0,0);
      muro->draw(modo_dibujado, edicion);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(159.0,0.0,320.0);
    glRotatef(180,0,1.0,0);
      muro->draw(modo_dibujado, edicion);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(160.0,0.0,160.0);
    glRotatef(270,0,1.0,0);
      muro->draw(modo_dibujado, edicion);
  glPopMatrix();

///////////////////////// SUELO ////////////////////////////////////

  glPushMatrix();
    glTranslatef(0.0,0.0,160.0);
  glPushMatrix();
      glScalef(8.0,8.0,8.0);
      glRotatef(90.0,-1.0,0.0,0.0);
        suelo->draw(modo_dibujado, edicion);
  glPopMatrix();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.0,0.0,320.0);
  glPushMatrix();
      glScalef(8.0,8.0,8.0);
      glRotatef(90.0,-1.0,0.0,0.0);
        suelo->draw(modo_dibujado, edicion);
  glPopMatrix();
  glPopMatrix();

///////////////////////// VENTANAS ////////////////////////////////////

    glPushMatrix();
      glTranslatef(1.0,20.0,100.0);
    glPushMatrix();
        glScalef(2.0,2.0,2.0);
        glRotatef(90.0,0.0,1.0,0.0);
          ventana->draw(modo_dibujado, edicion);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(159.0,20.0,59.0);
    glPushMatrix();
        glScalef(2.0,2.0,2.0);
        glRotatef(270.0,0.0,1.0,0.0);
          ventana->draw(modo_dibujado, edicion);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(1.0,20.0,260.0);
    glPushMatrix();
        glScalef(2.0,2.0,2.0);
        glRotatef(90.0,0.0,1.0,0.0);
          ventana->draw(modo_dibujado, edicion);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(159.0,20.0,209.0);
    glPushMatrix();
        glScalef(2.0,2.0,2.0);
        glRotatef(270.0,0.0,1.0,0.0);
          ventana->draw(modo_dibujado, edicion);
    glPopMatrix();
    glPopMatrix();

  glPushMatrix();
    glScalef(10,10,10);
    glTranslatef(4,1.4,4);
      peon->draw(modo_dibujado, edicion, hayTapas);
    glPopMatrix();

   glPushMatrix();
    glTranslatef(120,0,40);
      cilindro->draw(modo_dibujado, edicion,hayTapas);
    glPopMatrix();


  glPushMatrix();
    glTranslatef(100.0,0.0,100.0);
    glScalef(0.5,0.5,0.5);
    robot->draw(modo_dibujado, edicion, material2,hayTapas);
    glPopMatrix();

  glPushMatrix();
    glTranslatef(80,0,40);
      cono->draw(modo_dibujado, edicion,hayTapas);
    glPopMatrix();

  glPushMatrix();
    glTranslatef(30,10,80);
      esfera->draw(modo_dibujado, edicion,hayTapas);
    glPopMatrix();


    if(cuboActivado == 1){
    glPushMatrix();
    glTranslatef(60,0,60);
    cubo->draw(modo_dibujado, edicion);
    glPopMatrix();
    }

 if(tetraedroActivado == 1){
    glPushMatrix();
    glTranslatef(60,0,60);
    tetraedro->draw(modo_dibujado, edicion);
    glPopMatrix();
  }




}


bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA)
            modoMenu=NADA;
         else {
            salir=true ;
         }
         break ;
      case 'O' :
         modoMenu=SELOBJETO;
         cout << "---MODO DE SELECCION DE OBJETO ACTIVADO--- " << endl;
         cout << " C) Visualiza/oculta el Cubo" << endl;
         cout << " T) Visualiza/oculta el Tetraedro" << endl;
         cout << " Q) Salir" << endl;
         cout << endl;
         break ;
      case 'C' :
          if (modoMenu == SELOBJETO){

            cuboActivado = (cuboActivado + 1) % 2;
            if(cuboActivado){
              cout << " : : CUBO ACTIVADO : : " << endl;
            }else{
              cout << " : : CUBO DESACTIVADO : : " << endl;
            }
          }else if(modoMenu = SELVISUALIZACION){
            modoMenu = SELCAMARA;
            cout << "  :  :  SELECCION DE CAMARA ACTIVADO  :  :"<<endl;
            cout << "0-2) Seleccione una camara";
          }else{
            cout << "[ERROR] Asegurese que está el modo de selección de objeto activado" << endl;
          }
          cout << endl;
      break;
      case 'T' :
          if (modoMenu == SELOBJETO){
            tetraedroActivado= (tetraedroActivado + 1) % 2;
            if(tetraedroActivado){
              cout << " : : TETRAEDRO ACTIVADO : : " << endl;
            }else{
              cout << " : : TETRAEDRO DESACTIVADO : : " << endl;
            }
          }else if(modoMenu == SELVISUALIZACION){
            tapaActivada = (tapaActivada + 1) % 2;
            if(tapaActivada == 1){
              hayTapas = true;
              cout << " : : TAPAS ACTIVADAS : : " << endl;
            }else{
              hayTapas = false;
              cout << " : : TAPAS DESACTIVADAS : : " << endl;
            }

          }else{
            cout << "[ERROR] Asegurese que está el modo de selección de objeto activado" << endl;
          }
          cout << endl;
      break;
      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         if(modoMenu != SELVISUALIZACION){
         modoMenu=SELVISUALIZACION;
         cout << "---MODO DE SELECCION DE MODO DE VISUALIZACION ACTIVADO--- " << endl;
         cout << " P) Activa/desactiva la visualización en modo puntos" << endl;
         cout << " L) Activa/desactiva la visualización en modo líneas" << endl;
         cout << " S) Activa/desactiva la visualización en modo sólido" << endl;
         cout << " A) Activa/desactiva la visualización en modo ajedrez" << endl;
         cout << " I) Activa/desactiva la visualización con iluminación" << endl;
         cout << " J) Activa/desactiva la animacion automática del objeto jerárquico" << endl;
         cout << " V) Se mueve manualmente el grado de libertad del objeto jerárquico" << endl;
         cout << " T) Activa/desactiva las tapas de los objetos de revolución" << endl;
         cout << " Q) Salir" << endl;
         cout << endl;
         }else{
          modoMenu=SELOBJETOJERARQUICO;
          cout << "---SELECCION DE GRADO DE LIBERTAD ACTIVADO--- " << endl;
          cout << " 0-7) Seleccionar grado de libertad" << endl;
          cout << " +) Aumentar valor aplicado al grado de libertad" << endl;
          cout << " -) Disminuir valor aplicado al grado de libertad" << endl;
          cout << " Q) Salir" << endl;
         }
      break ;
      case 'P' :
         if (modoMenu == SELVISUALIZACION || modoMenu == SELOBJETOJERARQUICO){
             if(!edicion[0]){
              edicion[0] = true;
              edicion[3] = false;
              cout << " : : VISUALIZACION EN MODO PUNTOS ACTIVADA : : " << endl;
             }else{
              edicion[0] = false;
              modoMenu = SELVISUALIZACION;
              cout << " : : VISUALIZACION EN MODO PUNTOS DESACTIVADA : : " << endl;
             }
        }else if(modoMenu == SELILUMINACION || modoMenu == SELOBJETOJERARQUICO){
               modoMenu = SELILUAUTO;
               cout << " : : LUZ AUTOMÁTICA ACTIVADA : : " << endl;
        }else if(modoMenu == SELILUAUTO){
               modoMenu = SELILUMINACION;
               cout << " : : LUZ AUTOMÁTICA DESACTIVADA : : " << endl;
        }else{
           cout << "[ERROR] Asegurese que está el modo de selección de modo de visualización activado" << endl;
        }
        cout << endl;
      break;
      case 'L' :
         if (modoMenu == SELVISUALIZACION || modoMenu == SELOBJETOJERARQUICO){
           if(!edicion[1]){
            edicion[1] = true;
            edicion[3] = false;
            cout << " : : VISUALIZACION EN MODO LÍNEAS ACTIVADA : : " << endl;
           }else{
            edicion[1] = false;
            cout << " : : VISUALIZACION EN MODO LÍNEAS DESACTIVADA : : " << endl;
           }

        }else{
           cout << "[ERROR] Asegurese que está el modo de selección de modo de visualización activado" << endl;
        }
        cout << endl;
      break;
      case 'S' :
         if (modoMenu == SELVISUALIZACION || modoMenu == SELOBJETOJERARQUICO){
           if(!edicion[2]){
            edicion[2] = true;
            edicion[3] = false;
            cout << " : : VISUALIZACION EN MODO SÓLIDO ACTIVADA : : " << endl;
           }else{
            edicion[2] = false;
            cout << " : : VISUALIZACION EN MODO SÓLIDO DESACTIVADA : : " << endl;
           }

        }else{
           cout << "[ERROR] Asegurese que está el modo de selección de modo de visualización activado" << endl;
        }
        cout << endl;
      break;
      case 'A' :
          if(modoMenu == SELVISUALIZACION || modoMenu == SELOBJETOJERARQUICO){
            modo_ajedrez = (modo_ajedrez + 1) % 2;
           if(modo_ajedrez == 1){
            cout << " : : VISUALIZACION EN MODO AJEDREZ ACTIVADA : : " << endl;
           }else{
            cout << " : : VISUALIZACION EN MODO AJEDREZ DESACTIVADA : : " << endl;
           }

          }else if (modoMenu == SELILUMINACION){
            cout << " : : ANGULO ALFA SELECCIONADO : : " << endl;
            angulo_escogido = 'a';
        }else{
           cout << "[ERROR] Asegurese que está el modo de selección de modo de visualización activado" << endl;
        }
        cout << endl;
      break;
      case 'B' :
        if(modoMenu == SELILUMINACION){
          cout << " : : ANGULO BETA SELECCIONADO : : " << endl;
          angulo_escogido = 'b';
        }
      break;
      case 'I' :
         if (modoMenu == SELVISUALIZACION || modoMenu == SELOBJETOJERARQUICO){
           if(!edicion[3]){
            modo_ajedrez =0;
            modoMenu = SELILUMINACION;
            edicion[3] = true;
            cout << " : : VISUALIZACION CON ILUMINACION ACTIVADA : : " << endl;
            cout << " 0 a 2) Activa/desactiva la luz seleccionada" << endl;
            cout << " A) Activa/desactiva modo variación del ángulo alfa" << endl;
            cout << " B) Activa/desactiva modo variación del ángulo beta" << endl;
            cout << " >) Activa/desactiva incrementa el ángulo" << endl;
            cout << " <) Activa/desactiva decrementa el ángulo" << endl;
            cout << " P) Activa/desactiva iluminación automática" << endl;
            cout << " Q) Salir" << endl;
           }else{
            edicion[3] = false;
            modoMenu = SELVISUALIZACION;
            cout << " : : VISUALIZACION CON ILUMINACION DESACTIVADA : : " << endl;
           }
        }else{
           cout << "[ERROR] Asegurese que está el modo de selección de modo de visualización activado" << endl;
        }
        cout << endl;
      break;
      case 'J':
        if(modoMenu == SELVISUALIZACION){
          modoMenu = SELANIMACIONAUTO;
          velocidad = 2;
          cout << "---ANIMACION AUTOMATICA ACTIVADA--- " << endl;
          cout << " +) Aumentar velocidad animación" << endl;
          cout << " -) Disminuir velocidad animación" << endl;
        }else if(modoMenu == SELANIMACIONAUTO){
          modoMenu = SELVISUALIZACION;
        }
      break;
      case '>' :
        if(modoMenu == SELILUMINACION){
          if(angulo_escogido == 'a'){
            luz_0->variarAnguloAlpha(0.3);
            cout << " : : INCREMENTO DEL ANGULO ALFA : :" << endl;
          }
          else if(angulo_escogido == 'b'){
            luz_0->variarAnguloBeta(0.3);
            cout << " : : INCREMENTO DEL ANGULO BETA : :" << endl;
          }
          else
              cout << " : : DEBE ESCOGER UN ANGULO PRIMERO : :" << endl;
        }
        break;

      case '<' :
        if(modoMenu == SELILUMINACION){
          if(angulo_escogido == 'a'){
            luz_0->variarAnguloAlpha(-0.3);
            cout << " : : DECREMENTO DEL ANGULO ALFA : :" << endl;
          }
          else if(angulo_escogido == 'b'){
            luz_0->variarAnguloBeta(-0.3);
            cout << " : : DECREMENTO DEL ANGULO BETA : :" << endl;
          }
          else
              cout << " : : DEBE ESCOGER UN ANGULO PRIMERO : :" << endl;
        }
        break;

       case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         cout << "---MODO DE SELECCION DE MODO DE DIBUJADO ACTIVADO--- " << endl;
         cout << " 1) Visualicación usando glDrawElements" << endl;
         cout << " 2) Visualización usando VBOs" << endl;
         cout << " Q) Salir" << endl;
         cout << endl;
         break ;
      case '0' :
        if(modoMenu == SELILUMINACION){
          if(!lucesActivadas[0] && luz_0 != nullptr){
            lucesActivadas[0]=true;
            cout << " : : LUZ 0 ACTIVADA : :" << endl;
          }
          else{
            lucesActivadas[0] = false;
            cout << " : : LUZ 0 DESACTIVADA : :" << endl;
          }
        }else if(modoMenu == SELOBJETOJERARQUICO){
          cout << "Grado de libertad de la altura de la cabeza seleccionado" << endl;
          gradoEscogido = 0;
        }else if(modoMenu == SELCAMARA){
          camaraActiva = 0;
          cout << "  :  : CAMARA 0 ACTIVADA :  :  " << endl;
          switch (camaraApunta[0]) {
            case 0: std::cout << " : : CUBO SELECCIONADO : :" << std::endl;
              cubo->aplicarColor(colorSeleccion);
              cubo->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(72.5,12.5,72.5);
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 1: std::cout << " : : TETRAEDRO SELECCIONADO : :" << std::endl;
              tetraedro->aplicarColor(colorSeleccion);
              tetraedro->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(65.772,8.66,70);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 2: std::cout << " : : PEON SELECCIONADO : :" << std::endl;
              peon->aplicarColor(colorSeleccion);
              peon->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(40,14,40);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 3: std::cout << " : : CONO SELECCIONADO : :" << std::endl;
              cono->aplicarColor(colorSeleccion);
              cono->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(80,12.5,40);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 4: std::cout << " : : CILINDRO SELECCIONADO : :" << std::endl;
              cilindro->aplicarColor(colorSeleccion);
              cilindro->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(120,12.5,40);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 5: std::cout << " : : ESFERA SELECCIONADO : :" << std::endl;
              esfera->aplicarColor(colorSeleccion);
              esfera->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(30,10,80);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 6: std::cout << " : : MURO SELECCIONADO : :" << std::endl;
              muro->aplicarColor(colorSeleccion);
              muro->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(80.0,40.0,0.0);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 7: std::cout << " : : SUELO SELECCIONADO : :" << std::endl;
              suelo->aplicarColor(colorSeleccion);
              suelo->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(80.0,0.0,240.0);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 8: std::cout << " : : VENTANA SELECCIONADO : :" << std::endl;
              ventana->aplicarColor(colorSeleccion);
              ventana->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(1.0,40.0,80.0);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 9: std::cout << " : : ROBOT SELECCIONADO : :" << std::endl;
              robot->aplicarColor(colorSeleccion);
              robot->aplicarMaterialTotal(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(100,20,100);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              seleccionActiva = true;
            break;
            case -1:
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = false;
            break;
            case 10:
            robot->aplicarColor(Tupla3f(0,1,0));
            robot->aplicarMaterialTotal(material1);
            camarasActivadas[camaraActiva].setObjetivo(0,0,0);
            cubo->aplicarMaterial(material3);
            cubo->aplicarColor(Tupla3f(0,0,1));
            tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
            tetraedro->aplicarMaterial(material2);
            peon->aplicarColor(Tupla3f(0,1,0));
            peon->aplicarMaterial(material1);
            cono->aplicarColor(Tupla3f(0,1,0));
            cono->aplicarMaterial(material2);
            cilindro->aplicarColor(Tupla3f(0,1,0));
            cilindro->aplicarMaterial(material3);
            esfera->aplicarColor(Tupla3f(0,1,0));
            esfera->aplicarMaterial(material3);
            muro->aplicarColor(Tupla3f(0,1,1));
            muro->aplicarMaterial(material1);
            suelo->aplicarColor(Tupla3f(0,0,0.2));
            suelo->aplicarMaterial(material1);
            ventana->aplicarColor(Tupla3f(0,0.2,0));
            ventana->aplicarMaterial(material1);
            seleccionActiva = false;
            break;
          }

          change_observer();
          change_projection(1) ;
        }
        break;
      case '1' :
        if(modoMenu == SELILUMINACION){
          if(!lucesActivadas[1] && luz_1 != nullptr){
            lucesActivadas[1]=true;
            cout << " : : LUZ 1 ACTIVADA : :" << endl;
          }
          else{
            lucesActivadas[1]=false;
            cout << " : : LUZ 1 DESACTIVADA : :" << endl;
          }
        }else if(modoMenu == SELDIBUJADO){
           cout << " : : VISUALIZACION USANDO glDrawElements ACTIVADA : : " << endl;
           modo_dibujado = 1;
        }else if(modoMenu == SELOBJETOJERARQUICO){
          cout << "Grado de libertad del angulo Y de la cabeza seleccionado" << endl;
          gradoEscogido = 1;
        }else if(modoMenu == SELCAMARA){
          camaraActiva = 1;
          cout << "  :  : CAMARA 1 ACTIVADA :  :  " << endl;
          switch (camaraApunta[1]) {
            case 0: std::cout << " : : CUBO SELECCIONADO : :" << std::endl;
              cubo->aplicarColor(colorSeleccion);
              cubo->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(72.5,12.5,72.5);
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 1: std::cout << " : : TETRAEDRO SELECCIONADO : :" << std::endl;
              tetraedro->aplicarColor(colorSeleccion);
              tetraedro->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(65.772,8.66,70);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 2: std::cout << " : : PEON SELECCIONADO : :" << std::endl;
              peon->aplicarColor(colorSeleccion);
              peon->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(40,14,40);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 3: std::cout << " : : CONO SELECCIONADO : :" << std::endl;
              cono->aplicarColor(colorSeleccion);
              cono->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(80,12.5,40);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 4: std::cout << " : : CILINDRO SELECCIONADO : :" << std::endl;
              cilindro->aplicarColor(colorSeleccion);
              cilindro->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(120,12.5,40);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 5: std::cout << " : : ESFERA SELECCIONADO : :" << std::endl;
              esfera->aplicarColor(colorSeleccion);
              esfera->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(30,10,80);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 6: std::cout << " : : MURO SELECCIONADO : :" << std::endl;
              muro->aplicarColor(colorSeleccion);
              muro->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(80.0,40.0,0.0);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 7: std::cout << " : : SUELO SELECCIONADO : :" << std::endl;
              suelo->aplicarColor(colorSeleccion);
              suelo->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(80.0,0.0,240.0);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 8: std::cout << " : : VENTANA SELECCIONADO : :" << std::endl;
              ventana->aplicarColor(colorSeleccion);
              ventana->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(1.0,40.0,80.0);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 9: std::cout << " : : ROBOT SELECCIONADO : :" << std::endl;
              robot->aplicarColor(colorSeleccion);
              robot->aplicarMaterialTotal(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(100,20,100);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              seleccionActiva = true;
            break;
            case -1:
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = false;
            break;
            case 10:
            robot->aplicarColor(Tupla3f(0,1,0));
            robot->aplicarMaterialTotal(material1);
            camarasActivadas[camaraActiva].setObjetivo(0,0,0);
            cubo->aplicarMaterial(material3);
            cubo->aplicarColor(Tupla3f(0,0,1));
            tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
            tetraedro->aplicarMaterial(material2);
            peon->aplicarColor(Tupla3f(0,1,0));
            peon->aplicarMaterial(material1);
            cono->aplicarColor(Tupla3f(0,1,0));
            cono->aplicarMaterial(material2);
            cilindro->aplicarColor(Tupla3f(0,1,0));
            cilindro->aplicarMaterial(material3);
            esfera->aplicarColor(Tupla3f(0,1,0));
            esfera->aplicarMaterial(material3);
            muro->aplicarColor(Tupla3f(0,1,1));
            muro->aplicarMaterial(material1);
            suelo->aplicarColor(Tupla3f(0,0,0.2));
            suelo->aplicarMaterial(material1);
            ventana->aplicarColor(Tupla3f(0,0.2,0));
            ventana->aplicarMaterial(material1);
            seleccionActiva = false;
            break;
          }
          change_observer();
          change_projection(1) ;
        }else{
           cout << "[ERROR] Asegurese que está el modo de selección de modo de dibujado activado" << endl;
        }
        cout << endl;
      break;
      case '2' :
        if(modoMenu == SELILUMINACION){
          if(!lucesActivadas[2] && luz_2 != nullptr){
            luz_2->activar();
            lucesActivadas[2]=true;
            cout << " : : LUZ 2 ACTIVADA : :" << endl;
          }
          else{
            luz_2->desactivar();
            lucesActivadas[2]=false;
            cout << " : : LUZ 2 DESACTIVADA : :" << endl;
          }
        }else if(modoMenu == SELDIBUJADO){
           cout << " : : VISUALIZACION USANDO VBOs ACTIVADA : : " << endl;
           modo_dibujado = 2;
        }else if(modoMenu == SELOBJETOJERARQUICO){
          cout << "Grado de libertad del ángulo X del brazo Izquierdo seleccionado" << endl;
          gradoEscogido = 2;
         }else if(modoMenu == SELCAMARA){
          camaraActiva = 2;
          cout << "  :  : CAMARA 2 ACTIVADA :  :  " << endl;
          switch (camaraApunta[2]) {
            case 0: std::cout << " : : CUBO SELECCIONADO : :" << std::endl;
              cubo->aplicarColor(colorSeleccion);
              cubo->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(72.5,12.5,72.5);
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 1: std::cout << " : : TETRAEDRO SELECCIONADO : :" << std::endl;
              tetraedro->aplicarColor(colorSeleccion);
              tetraedro->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(65.772,8.66,70);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 2: std::cout << " : : PEON SELECCIONADO : :" << std::endl;
              peon->aplicarColor(colorSeleccion);
              peon->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(40,14,40);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 3: std::cout << " : : CONO SELECCIONADO : :" << std::endl;
              cono->aplicarColor(colorSeleccion);
              cono->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(80,12.5,40);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 4: std::cout << " : : CILINDRO SELECCIONADO : :" << std::endl;
              cilindro->aplicarColor(colorSeleccion);
              cilindro->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(120,12.5,40);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 5: std::cout << " : : ESFERA SELECCIONADO : :" << std::endl;
              esfera->aplicarColor(colorSeleccion);
              esfera->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(30,10,80);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 6: std::cout << " : : MURO SELECCIONADO : :" << std::endl;
              muro->aplicarColor(colorSeleccion);
              muro->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(80.0,40.0,0.0);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 7: std::cout << " : : SUELO SELECCIONADO : :" << std::endl;
              suelo->aplicarColor(colorSeleccion);
              suelo->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(80.0,0.0,240.0);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 8: std::cout << " : : VENTANA SELECCIONADO : :" << std::endl;
              ventana->aplicarColor(colorSeleccion);
              ventana->aplicarMaterial(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(1.0,40.0,80.0);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = true;
            break;
            case 9: std::cout << " : : ROBOT SELECCIONADO : :" << std::endl;
              robot->aplicarColor(colorSeleccion);
              robot->aplicarMaterialTotal(materialSeleccion);
              camarasActivadas[camaraActiva].setObjetivo(100,20,100);
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              seleccionActiva = true;
            break;
            case 10:
            robot->aplicarColor(Tupla3f(0,1,0));
            robot->aplicarMaterialTotal(material1);
            camarasActivadas[camaraActiva].setObjetivo(0,0,0);
            cubo->aplicarMaterial(material3);
            cubo->aplicarColor(Tupla3f(0,0,1));
            tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
            tetraedro->aplicarMaterial(material2);
            peon->aplicarColor(Tupla3f(0,1,0));
            peon->aplicarMaterial(material1);
            cono->aplicarColor(Tupla3f(0,1,0));
            cono->aplicarMaterial(material2);
            cilindro->aplicarColor(Tupla3f(0,1,0));
            cilindro->aplicarMaterial(material3);
            esfera->aplicarColor(Tupla3f(0,1,0));
            esfera->aplicarMaterial(material3);
            muro->aplicarColor(Tupla3f(0,1,1));
            muro->aplicarMaterial(material1);
            suelo->aplicarColor(Tupla3f(0,0,0.2));
            suelo->aplicarMaterial(material1);
            ventana->aplicarColor(Tupla3f(0,0.2,0));
            ventana->aplicarMaterial(material1);
            seleccionActiva = false;
            break;
            case -1:
              cubo->aplicarMaterial(material3);
              cubo->aplicarColor(Tupla3f(0,0,1));
              tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
              tetraedro->aplicarMaterial(material2);
              peon->aplicarColor(Tupla3f(0,1,0));
              peon->aplicarMaterial(material1);
              cono->aplicarColor(Tupla3f(0,1,0));
              cono->aplicarMaterial(material2);
              cilindro->aplicarColor(Tupla3f(0,1,0));
              cilindro->aplicarMaterial(material3);
              esfera->aplicarColor(Tupla3f(0,1,0));
              esfera->aplicarMaterial(material3);
              muro->aplicarColor(Tupla3f(0,1,1));
              muro->aplicarMaterial(material1);
              suelo->aplicarColor(Tupla3f(0,0,0.2));
              suelo->aplicarMaterial(material1);
              ventana->aplicarColor(Tupla3f(0,0.2,0));
              ventana->aplicarMaterial(material1);
              robot->aplicarColor(Tupla3f(0,1,0));
              robot->aplicarMaterialTotal(material1);
              seleccionActiva = false;
            break;
          }
          change_observer();
          change_projection(1) ;
         }else{
           cout << "[ERROR] Asegurese que está el modo de selección de modo de dibujado activado" << endl;
         }
         cout << endl;
         break;
        case '3' :
        if(modoMenu == SELILUMINACION){
          if(!lucesActivadas[3] && luz_3 != nullptr){
            lucesActivadas[3]=true;
            cout << " : : LUZ 3 ACTIVADA : :" << endl;
          }else{
            lucesActivadas[3] = false;
            cout << " : : LUZ 3 DESACTIVADA : :" << endl;
          }
        }else if(modoMenu == SELOBJETOJERARQUICO){
          cout << "Grado de libertad del ángulo Z del brazo Izquierdo seleccionado" << endl;
          gradoEscogido = 3;
        }
        break;
        case '4':
          if(modoMenu == SELOBJETOJERARQUICO){
            cout << "Grado de libertad del ángulo X del brazo Derecho seleccionado" << endl;
            gradoEscogido = 4;

          }
        break;

        case '5':
          if(modoMenu == SELOBJETOJERARQUICO){
            cout << "Grado de libertad del ángulo Z del brazo Derecho seleccionado" << endl;
            gradoEscogido = 5;
          }

        break;
        case '6':
          if(modoMenu == SELOBJETOJERARQUICO){
            cout << "Grado de libertad del ángulo X de la pierna Izquierda seleccionada" << endl;
            gradoEscogido = 6;
          }

        break;
        case '7':
          if(modoMenu == SELOBJETOJERARQUICO){
            cout << "Grado de libertad del ángulo X de la pierna Izquierda seleccionada" << endl;
            gradoEscogido = 7;
          }
        break;
        case '+':
          if(modoMenu == SELOBJETOJERARQUICO){
            switch (gradoEscogido){
            case 0:
              robot->cambiarAlturaCabeza(4);
            break;
            case 1:
              robot->cambiarAnguloCabezaY(4);
            break;
            case 2:
              robot->cambiarAnguloBrazoIzqX(4);
            break;
            case 3:
              robot->cambiarAnguloBrazoIzqZ(4);
            break;
            case 4:
              robot->cambiarAnguloBrazoDerX(4);
            break;
            case 5:
              robot->cambiarAnguloBrazoDerZ(4);
            break;
            case 6:
              robot->cambiarAnguloPiernaIzqX(4);
            break;
            case 7:
              robot->cambiarAnguloPiernaDerX(4);
            break;
            }
          }else if(modoMenu == SELANIMACIONAUTO){
            velocidad +=0.5;
          }
        break;
        case '-':
          if(modoMenu == SELOBJETOJERARQUICO){
          switch (gradoEscogido){
            case 0:
              robot->cambiarAlturaCabeza(-4);
            break;
            case 1:
              robot->cambiarAnguloCabezaY(-4);
            break;
            case 2:
              robot->cambiarAnguloBrazoIzqX(-4);
            break;
            case 3:
              robot->cambiarAnguloBrazoIzqZ(-4);
            break;
            case 4:
              robot->cambiarAnguloBrazoDerX(-4);
            break;
            case 5:
              robot->cambiarAnguloBrazoDerZ(-4);
            break;
            case 6:
              robot->cambiarAnguloPiernaIzqX(-4);
            break;
            case 7:
              robot->cambiarAnguloPiernaDerX(-4);
            break;
            }

          }else if(modoMenu == SELANIMACIONAUTO){
            velocidad -=0.5;
          }

        break;
   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         camarasActivadas[camaraActiva].rotarXExaminar(-1);
         break;
	   case GLUT_KEY_RIGHT:
         camarasActivadas[camaraActiva].rotarXExaminar(1);
         break;
	   case GLUT_KEY_UP:
         camarasActivadas[camaraActiva].rotarYExaminar(1);
         break;
	   case GLUT_KEY_DOWN:
         camarasActivadas[camaraActiva].rotarYExaminar(-1);
         break;
	   case GLUT_KEY_PAGE_UP:
         camarasActivadas[camaraActiva].zoom(1.03);
         change_projection(1) ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         camarasActivadas[camaraActiva].zoom(0.97);
         change_projection(1) ;
         break;
	}


}


void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   camarasActivadas[camaraActiva].setProyeccion() ;
}


void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

void Escena::change_observer()
{
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   camarasActivadas[camaraActiva].setObserver();
}

void Escena::animarModeloJerarquico(){
  robot->animarRobot(velocidad);
}

void Escena::animarLuzPuntual(){
  if(modoMenu == SELILUAUTO){
    lucesActivadas[1]=true;
    lucesActivadas[0]=false;
    lucesActivadas[2]=false;
    lucesActivadas[3]=false;
    luz_1->animarLuz();
  }

}

void Escena::dibujarSimple(){


  glDrawBuffer(GL_BACK) ;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
  glDisable (GL_DITHER) ;
  glDisable(GL_LIGHTING) ;
  glDisable (GL_TEXTURE_2D) ;

  muro->drawSimple();

  glPushMatrix();
    glTranslatef(0.0,0.0,160.0);
    glRotatef(90,0,1.0,0);
      muro->drawSimple();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(159.0,0.0,160.0);
    glRotatef(180,0,1.0,0);
      muro->drawSimple();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(160.0,0.0,0.0);
    glRotatef(270,0,1.0,0);
      muro->drawSimple();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.0,0.0,160.0);
      muro->drawSimple();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.0,0.0,320.0);
    glRotatef(90,0,1.0,0);
      muro->drawSimple();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(159.0,0.0,320.0);
    glRotatef(180,0,1.0,0);
      muro->drawSimple();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(160.0,0.0,160.0);
    glRotatef(270,0,1.0,0);
      muro->drawSimple();
  glPopMatrix();

///////////////////////// SUELO ////////////////////////////////////

  glPushMatrix();
    glTranslatef(0.0,0.0,160.0);
  glPushMatrix();
      glScalef(8.0,8.0,8.0);
      glRotatef(90.0,-1.0,0.0,0.0);
        suelo->drawSimple();
  glPopMatrix();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.0,0.0,320.0);
  glPushMatrix();
      glScalef(8.0,8.0,8.0);
      glRotatef(90.0,-1.0,0.0,0.0);
        suelo->drawSimple();
  glPopMatrix();
  glPopMatrix();

///////////////////////// VENTANAS ////////////////////////////////////

    glPushMatrix();
      glTranslatef(1.0,20.0,100.0);
    glPushMatrix();
        glScalef(2.0,2.0,2.0);
        glRotatef(90.0,0.0,1.0,0.0);
          ventana->drawSimple();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(159.0,20.0,59.0);
    glPushMatrix();
        glScalef(2.0,2.0,2.0);
        glRotatef(270.0,0.0,1.0,0.0);
          ventana->drawSimple();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(1.0,20.0,260.0);
    glPushMatrix();
        glScalef(2.0,2.0,2.0);
        glRotatef(90.0,0.0,1.0,0.0);
          ventana->drawSimple();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(159.0,20.0,209.0);
    glPushMatrix();
        glScalef(2.0,2.0,2.0);
        glRotatef(270.0,0.0,1.0,0.0);
          ventana->drawSimple();
    glPopMatrix();
    glPopMatrix();

  glPushMatrix();
    glScalef(10,10,10);
    glTranslatef(4,1.4,4);
      peon->drawSimple();
    glPopMatrix();

   glPushMatrix();
    glTranslatef(120,0,40);
      cilindro->drawSimple();
    glPopMatrix();

  glPushMatrix();
    glTranslatef(100.0,0.0,100.0);
    glScalef(0.5,0.5,0.5);
    robot->drawSimple();
    glPopMatrix();

  glPushMatrix();
    glTranslatef(80,0,40);
      cono->drawSimple();
    glPopMatrix();

  glPushMatrix();
    glTranslatef(30,10,80);
      esfera->drawSimple();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(100.0,0.0,100.0);
      glScalef(0.5,0.5,0.5);
      robot->drawSimple();
    glPopMatrix();


    if(cuboActivado == 1){
    glPushMatrix();
    glTranslatef(60,0,60);
    cubo->drawSimple();
    glPopMatrix();
    }

    if(tetraedroActivado == 1){
       glPushMatrix();
       glTranslatef(60,0,60);
       tetraedro->drawSimple();
       glPopMatrix();
       }
glEnable(GL_DITHER);

}

int Escena::seleccionarObjeto(float x, float y){
  GLint viewport[4];
  GLubyte pixel_seleccionado[3];
  int objetoSeleccionado;

  glGetIntegerv(GL_VIEWPORT, viewport);
  glReadBuffer(GL_BACK);
  glReadPixels(x, viewport[3]-y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, (void *)pixel_seleccionado);

  if (pixel_seleccionado[0] == 0 && pixel_seleccionado[1] == 0 && pixel_seleccionado[2] == 255){
    objetoSeleccionado = 0; //cubo
  }else if (pixel_seleccionado[0] == 51 && pixel_seleccionado[1] == 51 && pixel_seleccionado[2] == 0){
    objetoSeleccionado = 1; //tetraedro
  }else if (pixel_seleccionado[0] == 0 && pixel_seleccionado[1] == 255 && pixel_seleccionado[2] == 0){
    objetoSeleccionado = 2; //peon
  }else if (pixel_seleccionado[0] == 255 && pixel_seleccionado[1] == 0 && pixel_seleccionado[2] == 0){
    objetoSeleccionado = 3; //cono
  }else if (pixel_seleccionado[0] == 255 && pixel_seleccionado[1] == 255 && pixel_seleccionado[2] == 0){
    objetoSeleccionado = 4; //cilindro
  }else if (pixel_seleccionado[0] == 255 && pixel_seleccionado[1] == 0 && pixel_seleccionado[2] == 255){
    objetoSeleccionado = 5; //esfera
  }else if (pixel_seleccionado[0] == 0 && pixel_seleccionado[1] == 255 && pixel_seleccionado[2] == 255){
    objetoSeleccionado = 6; //muro
  }else if (pixel_seleccionado[0] == 0 && pixel_seleccionado[1] == 0 && pixel_seleccionado[2] == 51){
    objetoSeleccionado = 7; //suelo
  }else if (pixel_seleccionado[0] == 0 && pixel_seleccionado[1] == 51 && pixel_seleccionado[2] == 0){
    objetoSeleccionado = 8; //ventana
  }else if (pixel_seleccionado[0] == 51 && pixel_seleccionado[1] == 0 && pixel_seleccionado[2] == 0){
    objetoSeleccionado = 9; //robot
  }else if (pixel_seleccionado[0] == 255 && pixel_seleccionado[1] == 255 && pixel_seleccionado[2] == 255){
    objetoSeleccionado = 10;
  }

  return objetoSeleccionado;

}

void Escena::clickRaton(int boton, int estado, float x, float y){
    switch (boton) {
      case GLUT_LEFT_BUTTON:
      dibujarSimple();
      objetoSeleccionado = seleccionarObjeto(x,y);

      if (estado == GLUT_DOWN) {
        anteriorX = x;
        anteriorY = y;
        if(camaraApunta[camaraActiva] != objetoSeleccionado){
          camaraApunta[camaraActiva] = objetoSeleccionado;
          seleccionActiva = true;
        switch (objetoSeleccionado) {
          case 0: std::cout << " : : CUBO SELECCIONADO : :" << std::endl;
            cubo->aplicarColor(colorSeleccion);
            cubo->aplicarMaterial(materialSeleccion);
            camarasActivadas[camaraActiva].setObjetivo(72.5,12.5,72.5);
            tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
            tetraedro->aplicarMaterial(material2);
            peon->aplicarColor(Tupla3f(0,1,0));
            peon->aplicarMaterial(material1);
            cono->aplicarColor(Tupla3f(0,1,0));
            cono->aplicarMaterial(material2);
            cilindro->aplicarColor(Tupla3f(0,1,0));
            cilindro->aplicarMaterial(material3);
            esfera->aplicarColor(Tupla3f(0,1,0));
            esfera->aplicarMaterial(material3);
            muro->aplicarColor(Tupla3f(0,1,1));
            muro->aplicarMaterial(material1);
            suelo->aplicarColor(Tupla3f(0,0,0.2));
            suelo->aplicarMaterial(material1);
            ventana->aplicarColor(Tupla3f(0,0.2,0));
            ventana->aplicarMaterial(material1);
            robot->aplicarColor(Tupla3f(0,1,0));
            robot->aplicarMaterialTotal(material1);
          break;
          case 1: std::cout << " : : TETRAEDRO SELECCIONADO : :" << std::endl;
            tetraedro->aplicarColor(colorSeleccion);
            tetraedro->aplicarMaterial(materialSeleccion);
            camarasActivadas[camaraActiva].setObjetivo(65.772,8.66,70);
            cubo->aplicarMaterial(material3);
            cubo->aplicarColor(Tupla3f(0,0,1));
            peon->aplicarColor(Tupla3f(0,1,0));
            peon->aplicarMaterial(material1);
            cono->aplicarColor(Tupla3f(0,1,0));
            cono->aplicarMaterial(material2);
            cilindro->aplicarColor(Tupla3f(0,1,0));
            cilindro->aplicarMaterial(material3);
            esfera->aplicarColor(Tupla3f(0,1,0));
            esfera->aplicarMaterial(material3);
            muro->aplicarColor(Tupla3f(0,1,1));
            muro->aplicarMaterial(material1);
            suelo->aplicarColor(Tupla3f(0,0,0.2));
            suelo->aplicarMaterial(material1);
            ventana->aplicarColor(Tupla3f(0,0.2,0));
            ventana->aplicarMaterial(material1);
            robot->aplicarColor(Tupla3f(0,1,0));
            robot->aplicarMaterialTotal(material1);
          break;
          case 2: std::cout << " : : PEON SELECCIONADO : :" << std::endl;
            peon->aplicarColor(colorSeleccion);
            peon->aplicarMaterial(materialSeleccion);
            camarasActivadas[camaraActiva].setObjetivo(40,14,40);
            cubo->aplicarMaterial(material3);
            cubo->aplicarColor(Tupla3f(0,0,1));
            tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
            tetraedro->aplicarMaterial(material2);
            cono->aplicarColor(Tupla3f(0,1,0));
            cono->aplicarMaterial(material2);
            cilindro->aplicarColor(Tupla3f(0,1,0));
            cilindro->aplicarMaterial(material3);
            esfera->aplicarColor(Tupla3f(0,1,0));
            esfera->aplicarMaterial(material3);
            muro->aplicarColor(Tupla3f(0,1,1));
            muro->aplicarMaterial(material1);
            suelo->aplicarColor(Tupla3f(0,0,0.2));
            suelo->aplicarMaterial(material1);
            ventana->aplicarColor(Tupla3f(0,0.2,0));
            ventana->aplicarMaterial(material1);
            robot->aplicarColor(Tupla3f(0,1,0));
            robot->aplicarMaterialTotal(material1);
          break;
          case 3: std::cout << " : : CONO SELECCIONADO : :" << std::endl;
            cono->aplicarColor(colorSeleccion);
            cono->aplicarMaterial(materialSeleccion);
            camarasActivadas[camaraActiva].setObjetivo(80,12.5,40);
            cubo->aplicarMaterial(material3);
            cubo->aplicarColor(Tupla3f(0,0,1));
            tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));;
            tetraedro->aplicarMaterial(material2);
            peon->aplicarColor(Tupla3f(0,1,0));
            peon->aplicarMaterial(material1);
            cilindro->aplicarColor(Tupla3f(0,1,0));
            cilindro->aplicarMaterial(material3);
            esfera->aplicarColor(Tupla3f(0,1,0));
            esfera->aplicarMaterial(material3);
            muro->aplicarColor(Tupla3f(0,1,1));
            muro->aplicarMaterial(material1);
            suelo->aplicarColor(Tupla3f(0,0,0.2));
            suelo->aplicarMaterial(material1);
            ventana->aplicarColor(Tupla3f(0,0.2,0));
            ventana->aplicarMaterial(material1);
            robot->aplicarColor(Tupla3f(0,1,0));
            robot->aplicarMaterialTotal(material1);
          break;
          case 4: std::cout << " : : CILINDRO SELECCIONADO : :" << std::endl;
            cilindro->aplicarColor(colorSeleccion);
            cilindro->aplicarMaterial(materialSeleccion);
            camarasActivadas[camaraActiva].setObjetivo(120,12.5,40);
            cubo->aplicarMaterial(material3);
            cubo->aplicarColor(Tupla3f(0,0,1));
            tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
            tetraedro->aplicarMaterial(material2);
            peon->aplicarColor(Tupla3f(0,1,0));
            peon->aplicarMaterial(material1);
            cono->aplicarColor(Tupla3f(0,1,0));
            cono->aplicarMaterial(material2);
            esfera->aplicarColor(Tupla3f(0,1,0));
            esfera->aplicarMaterial(material3);
            muro->aplicarColor(Tupla3f(0,1,1));
            muro->aplicarMaterial(material1);
            suelo->aplicarColor(Tupla3f(0,0,0.2));
            suelo->aplicarMaterial(material1);
            ventana->aplicarColor(Tupla3f(0,0.2,0));
            ventana->aplicarMaterial(material1);
            robot->aplicarColor(Tupla3f(0,1,0));
            robot->aplicarMaterialTotal(material1);
          break;
          case 5: std::cout << " : : ESFERA SELECCIONADO : :" << std::endl;
            esfera->aplicarColor(colorSeleccion);
            esfera->aplicarMaterial(materialSeleccion);
            camarasActivadas[camaraActiva].setObjetivo(30,10,80);
            cubo->aplicarMaterial(material3);
            cubo->aplicarColor(Tupla3f(0,0,1));
            tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
            tetraedro->aplicarMaterial(material2);
            peon->aplicarColor(Tupla3f(0,1,0));
            peon->aplicarMaterial(material1);
            cono->aplicarColor(Tupla3f(0,1,0));
            cono->aplicarMaterial(material2);
            cilindro->aplicarColor(Tupla3f(0,1,0));
            cilindro->aplicarMaterial(material3);
            muro->aplicarColor(Tupla3f(0,1,1));
            muro->aplicarMaterial(material1);
            suelo->aplicarColor(Tupla3f(0,0,0.2));
            suelo->aplicarMaterial(material1);
            ventana->aplicarColor(Tupla3f(0,0.2,0));
            ventana->aplicarMaterial(material1);
            robot->aplicarColor(Tupla3f(0,1,0));
            robot->aplicarMaterialTotal(material1);
          break;
          case 6: std::cout << " : : MURO SELECCIONADO : :" << std::endl;
            muro->aplicarColor(colorSeleccion);
            muro->aplicarMaterial(materialSeleccion);
            camarasActivadas[camaraActiva].setObjetivo(80.0,40.0,0.0);
            cubo->aplicarMaterial(material3);
            cubo->aplicarColor(Tupla3f(0,0,1));
            tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
            tetraedro->aplicarMaterial(material2);
            peon->aplicarColor(Tupla3f(0,1,0));
            peon->aplicarMaterial(material1);
            cono->aplicarColor(Tupla3f(0,1,0));
            cono->aplicarMaterial(material2);
            cilindro->aplicarColor(Tupla3f(0,1,0));
            cilindro->aplicarMaterial(material3);
            esfera->aplicarColor(Tupla3f(0,1,0));
            esfera->aplicarMaterial(material3);
            suelo->aplicarColor(Tupla3f(0,0,0.2));
            suelo->aplicarMaterial(material1);
            ventana->aplicarColor(Tupla3f(0,0.2,0));
            ventana->aplicarMaterial(material1);
            robot->aplicarColor(Tupla3f(0,1,0));
            robot->aplicarMaterialTotal(material1);
          break;
          case 7: std::cout << " : : SUELO SELECCIONADO : :" << std::endl;
            suelo->aplicarColor(colorSeleccion);
            suelo->aplicarMaterial(materialSeleccion);
            camarasActivadas[camaraActiva].setObjetivo(80.0,0.0,240.0);
            cubo->aplicarMaterial(material3);
            cubo->aplicarColor(Tupla3f(0,0,1));
            tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
            tetraedro->aplicarMaterial(material2);
            peon->aplicarColor(Tupla3f(0,1,0));
            peon->aplicarMaterial(material1);
            cono->aplicarColor(Tupla3f(0,1,0));
            cono->aplicarMaterial(material2);
            cilindro->aplicarColor(Tupla3f(0,1,0));
            cilindro->aplicarMaterial(material3);
            esfera->aplicarColor(Tupla3f(0,1,0));
            esfera->aplicarMaterial(material3);
            muro->aplicarColor(Tupla3f(0,1,1));
            muro->aplicarMaterial(material1);
            ventana->aplicarColor(Tupla3f(0,0.2,0));
            ventana->aplicarMaterial(material1);
            robot->aplicarColor(Tupla3f(0,1,0));
            robot->aplicarMaterialTotal(material1);
          break;
          case 8: std::cout << " : : VENTANA SELECCIONADO : :" << std::endl;
            ventana->aplicarColor(colorSeleccion);
            ventana->aplicarMaterial(materialSeleccion);
            camarasActivadas[camaraActiva].setObjetivo(1.0,40.0,80.0);
            cubo->aplicarMaterial(material3);
            cubo->aplicarColor(Tupla3f(0,0,1));
            tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
            tetraedro->aplicarMaterial(material2);
            peon->aplicarColor(Tupla3f(0,1,0));
            peon->aplicarMaterial(material1);
            cono->aplicarColor(Tupla3f(0,1,0));
            cono->aplicarMaterial(material2);
            cilindro->aplicarColor(Tupla3f(0,1,0));
            cilindro->aplicarMaterial(material3);
            esfera->aplicarColor(Tupla3f(0,1,0));
            esfera->aplicarMaterial(material3);
            muro->aplicarColor(Tupla3f(0,1,1));
            muro->aplicarMaterial(material1);
            suelo->aplicarColor(Tupla3f(0,0,0.2));
            suelo->aplicarMaterial(material1);
            robot->aplicarColor(Tupla3f(0,1,0));
            robot->aplicarMaterialTotal(material1);
          break;
          case 9: std::cout << " : : ROBOT SELECCIONADO : :" << std::endl;
            robot->aplicarColor(colorSeleccion);
            robot->aplicarMaterialTotal(materialSeleccion);
            camarasActivadas[camaraActiva].setObjetivo(100,20,100);
            cubo->aplicarMaterial(material3);
            cubo->aplicarColor(Tupla3f(0,0,1));
            tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
            tetraedro->aplicarMaterial(material2);
            peon->aplicarColor(Tupla3f(0,1,0));
            peon->aplicarMaterial(material1);
            cono->aplicarColor(Tupla3f(0,1,0));
            cono->aplicarMaterial(material2);
            cilindro->aplicarColor(Tupla3f(0,1,0));
            cilindro->aplicarMaterial(material3);
            esfera->aplicarColor(Tupla3f(0,1,0));
            esfera->aplicarMaterial(material3);
            muro->aplicarColor(Tupla3f(0,1,1));
            muro->aplicarMaterial(material1);
            suelo->aplicarColor(Tupla3f(0,0,0.2));
            suelo->aplicarMaterial(material1);
            ventana->aplicarColor(Tupla3f(0,0.2,0));
            ventana->aplicarMaterial(material1);

          break;
          case 10:
          robot->aplicarColor(Tupla3f(0,1,0));
          robot->aplicarMaterialTotal(material1);
          camarasActivadas[camaraActiva].setObjetivo(0,0,0);
          cubo->aplicarMaterial(material3);
          cubo->aplicarColor(Tupla3f(0,0,1));
          tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
          tetraedro->aplicarMaterial(material2);
          peon->aplicarColor(Tupla3f(0,1,0));
          peon->aplicarMaterial(material1);
          cono->aplicarColor(Tupla3f(0,1,0));
          cono->aplicarMaterial(material2);
          cilindro->aplicarColor(Tupla3f(0,1,0));
          cilindro->aplicarMaterial(material3);
          esfera->aplicarColor(Tupla3f(0,1,0));
          esfera->aplicarMaterial(material3);
          muro->aplicarColor(Tupla3f(0,1,1));
          muro->aplicarMaterial(material1);
          suelo->aplicarColor(Tupla3f(0,0,0.2));
          suelo->aplicarMaterial(material1);
          ventana->aplicarColor(Tupla3f(0,0.2,0));
          ventana->aplicarMaterial(material1);
          seleccionActiva = false;
          break;

        }

      }else if(camaraApunta[camaraActiva] == objetoSeleccionado){
          camaraApunta[camaraActiva] = -1;
          camarasActivadas[camaraActiva].setObjetivo(0,0,0);
          switch (objetoSeleccionado) {
            case 0: std::cout << " : : CUBO DESELECCIONADO : :" << std::endl;
            cubo->aplicarMaterial(material3);
            cubo->aplicarColor(Tupla3f(0,0,1));
            seleccionActiva = false;
            break;
            case 1: std::cout << " : : TETRAEDRO DESELECCIONADO : :" << std::endl;
            tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
            tetraedro->aplicarMaterial(material2);
            seleccionActiva = false;
            break;
            case 2: std::cout << " : : PEON DESELECCIONADO : :" << std::endl;
            peon->aplicarColor(Tupla3f(0,1,0));
            peon->aplicarMaterial(material1);
            seleccionActiva = false;
            break;
            case 3: std::cout << " : : CONO DESELECCIONADO : :" << std::endl;
            cono->aplicarColor(Tupla3f(0,1,0));
            cono->aplicarMaterial(material2);
            seleccionActiva = false;
            break;
            case 4: std::cout << " : : CILINDRO DESELECCIONADO : :" << std::endl;
            cilindro->aplicarColor(Tupla3f(0,1,0));
            cilindro->aplicarMaterial(material3);
            seleccionActiva = false;
            break;
            case 5: std::cout << " : : ESFERA DESELECCIONADO : :" << std::endl;
            esfera->aplicarColor(Tupla3f(0,1,0));
            esfera->aplicarMaterial(material3);
            seleccionActiva = false;
            break;
            case 6: std::cout << " : : MURO DESELECCIONADO : :" << std::endl;
            muro->aplicarColor(Tupla3f(0,1,1));
            muro->aplicarMaterial(material1);
            seleccionActiva = false;
            break;
            case 7: std::cout << " : : SUELO DESELECCIONADO : :" << std::endl;
            suelo->aplicarColor(Tupla3f(0,0,0.2));
            suelo->aplicarMaterial(material1);
            seleccionActiva = false;
            break;
            case 8: std::cout << " : : VENTANA DESELECCIONADO : :" << std::endl;
            ventana->aplicarColor(Tupla3f(0,0.2,0));
            ventana->aplicarMaterial(material1);
            seleccionActiva = false;
            break;
            case 9: std::cout << " : : ROBOT DESELECCIONADO : :" << std::endl;
            robot->aplicarColor(Tupla3f(0,1,0));
            robot->aplicarMaterialTotal(material1);
            seleccionActiva = false;
            break;
          }

      }
      change_observer() ;
      change_projection(1) ;
      }
      break;
      case GLUT_RIGHT_BUTTON:
        if(estado == GLUT_DOWN){
          btnizqpulsado = true;
        }else{
          btnizqpulsado = false;
        }
      break;
      case 3:
        camarasActivadas[camaraActiva].zoom(1.03);
        change_projection(1) ;
      break;
      case 4:
        camarasActivadas[camaraActiva].zoom(0.97);
        change_projection(1) ;
      break;
    }
  }


void Escena::ratonMovido(float x, float y){
  if(btnizqpulsado){

      std::cout << ": : RATON MOVIDO A x-->" << x << " y-->:" << y << " : :" <<std::endl;
      camarasActivadas[camaraActiva].rotarXExaminar(0.3*(x-anteriorX));
      camarasActivadas[camaraActiva].rotarYExaminar(1.1*(y-anteriorY));

      anteriorX = x;
      anteriorY = y;
  }
}

void Escena::ratonEncima(float x, float y){
  if(seleccionActiva == false){
  dibujarSimple();
  int objetoDebajo;
  objetoDebajo = seleccionarObjeto(x,y);
  switch (objetoDebajo) {
    case 0:
      cubo->aplicarColor(colorRatonEncima);
      cubo->aplicarMaterial(materialRatonEncima);

      tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
      tetraedro->aplicarMaterial(material2);
      peon->aplicarColor(Tupla3f(0,1,0));
      peon->aplicarMaterial(material1);
      cono->aplicarColor(Tupla3f(0,1,0));
      cono->aplicarMaterial(material2);
      cilindro->aplicarColor(Tupla3f(0,1,0));
      cilindro->aplicarMaterial(material3);
      esfera->aplicarColor(Tupla3f(0,1,0));
      esfera->aplicarMaterial(material3);
      muro->aplicarColor(Tupla3f(0,1,1));
      muro->aplicarMaterial(material1);
      suelo->aplicarColor(Tupla3f(0,0,0.2));
      suelo->aplicarMaterial(material1);
      ventana->aplicarColor(Tupla3f(0,0.2,0));
      ventana->aplicarMaterial(material1);
      robot->aplicarColor(Tupla3f(0,1,0));
      robot->aplicarMaterialTotal(material1);
    break;
    case 1:
      tetraedro->aplicarColor(colorRatonEncima);
      tetraedro->aplicarMaterial(materialRatonEncima);

      cubo->aplicarMaterial(material3);
      cubo->aplicarColor(Tupla3f(0,0,1));
      peon->aplicarColor(Tupla3f(0,1,0));
      peon->aplicarMaterial(material1);
      cono->aplicarColor(Tupla3f(0,1,0));
      cono->aplicarMaterial(material2);
      cilindro->aplicarColor(Tupla3f(0,1,0));
      cilindro->aplicarMaterial(material3);
      esfera->aplicarColor(Tupla3f(0,1,0));
      esfera->aplicarMaterial(material3);
      muro->aplicarColor(Tupla3f(0,1,1));
      muro->aplicarMaterial(material1);
      suelo->aplicarColor(Tupla3f(0,0,0.2));
      suelo->aplicarMaterial(material1);
      ventana->aplicarColor(Tupla3f(0,0.2,0));
      ventana->aplicarMaterial(material1);
      robot->aplicarColor(Tupla3f(0,1,0));
      robot->aplicarMaterialTotal(material1);
    break;
    case 2:
      peon->aplicarColor(colorRatonEncima);
      peon->aplicarMaterial(materialRatonEncima);

      cubo->aplicarMaterial(material3);
      cubo->aplicarColor(Tupla3f(0,0,1));
      tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
      tetraedro->aplicarMaterial(material2);
      cono->aplicarColor(Tupla3f(0,1,0));
      cono->aplicarMaterial(material2);
      cilindro->aplicarColor(Tupla3f(0,1,0));
      cilindro->aplicarMaterial(material3);
      esfera->aplicarColor(Tupla3f(0,1,0));
      esfera->aplicarMaterial(material3);
      muro->aplicarColor(Tupla3f(0,1,1));
      muro->aplicarMaterial(material1);
      suelo->aplicarColor(Tupla3f(0,0,0.2));
      suelo->aplicarMaterial(material1);
      ventana->aplicarColor(Tupla3f(0,0.2,0));
      ventana->aplicarMaterial(material1);
      robot->aplicarColor(Tupla3f(0,1,0));
      robot->aplicarMaterialTotal(material1);
    break;
    case 3:
      cono->aplicarColor(colorRatonEncima);
      cono->aplicarMaterial(materialRatonEncima);

      cubo->aplicarMaterial(material3);
      cubo->aplicarColor(Tupla3f(0,0,1));
      tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));;
      tetraedro->aplicarMaterial(material2);
      peon->aplicarColor(Tupla3f(0,1,0));
      peon->aplicarMaterial(material1);
      cilindro->aplicarColor(Tupla3f(0,1,0));
      cilindro->aplicarMaterial(material3);
      esfera->aplicarColor(Tupla3f(0,1,0));
      esfera->aplicarMaterial(material3);
      muro->aplicarColor(Tupla3f(0,1,1));
      muro->aplicarMaterial(material1);
      suelo->aplicarColor(Tupla3f(0,0,0.2));
      suelo->aplicarMaterial(material1);
      ventana->aplicarColor(Tupla3f(0,0.2,0));
      ventana->aplicarMaterial(material1);
      robot->aplicarColor(Tupla3f(0,1,0));
      robot->aplicarMaterialTotal(material1);
    break;
    case 4:
      cilindro->aplicarColor(colorRatonEncima);
      cilindro->aplicarMaterial(materialRatonEncima);

      cubo->aplicarMaterial(material3);
      cubo->aplicarColor(Tupla3f(0,0,1));
      tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
      tetraedro->aplicarMaterial(material2);
      peon->aplicarColor(Tupla3f(0,1,0));
      peon->aplicarMaterial(material1);
      cono->aplicarColor(Tupla3f(0,1,0));
      cono->aplicarMaterial(material2);
      esfera->aplicarColor(Tupla3f(0,1,0));
      esfera->aplicarMaterial(material3);
      muro->aplicarColor(Tupla3f(0,1,1));
      muro->aplicarMaterial(material1);
      suelo->aplicarColor(Tupla3f(0,0,0.2));
      suelo->aplicarMaterial(material1);
      ventana->aplicarColor(Tupla3f(0,0.2,0));
      ventana->aplicarMaterial(material1);
      robot->aplicarColor(Tupla3f(0,1,0));
      robot->aplicarMaterialTotal(material1);
    break;
    case 5:
      esfera->aplicarColor(colorRatonEncima);
      esfera->aplicarMaterial(materialRatonEncima);

      cubo->aplicarMaterial(material3);
      cubo->aplicarColor(Tupla3f(0,0,1));
      tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
      tetraedro->aplicarMaterial(material2);
      peon->aplicarColor(Tupla3f(0,1,0));
      peon->aplicarMaterial(material1);
      cono->aplicarColor(Tupla3f(0,1,0));
      cono->aplicarMaterial(material2);
      cilindro->aplicarColor(Tupla3f(0,1,0));
      cilindro->aplicarMaterial(material3);
      muro->aplicarColor(Tupla3f(0,1,1));
      muro->aplicarMaterial(material1);
      suelo->aplicarColor(Tupla3f(0,0,0.2));
      suelo->aplicarMaterial(material1);
      ventana->aplicarColor(Tupla3f(0,0.2,0));
      ventana->aplicarMaterial(material1);
      robot->aplicarColor(Tupla3f(0,1,0));
      robot->aplicarMaterialTotal(material1);
    break;
    case 6:
      muro->aplicarColor(colorRatonEncima);
      muro->aplicarMaterial(materialRatonEncima);

      cubo->aplicarMaterial(material3);
      cubo->aplicarColor(Tupla3f(0,0,1));
      tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
      tetraedro->aplicarMaterial(material2);
      peon->aplicarColor(Tupla3f(0,1,0));
      peon->aplicarMaterial(material1);
      cono->aplicarColor(Tupla3f(0,1,0));
      cono->aplicarMaterial(material2);
      cilindro->aplicarColor(Tupla3f(0,1,0));
      cilindro->aplicarMaterial(material3);
      esfera->aplicarColor(Tupla3f(0,1,0));
      esfera->aplicarMaterial(material3);
      suelo->aplicarColor(Tupla3f(0,0,0.2));
      suelo->aplicarMaterial(material1);
      ventana->aplicarColor(Tupla3f(0,0.2,0));
      ventana->aplicarMaterial(material1);
      robot->aplicarColor(Tupla3f(0,1,0));
      robot->aplicarMaterialTotal(material1);
    break;
    case 7:
      suelo->aplicarColor(colorRatonEncima);
      suelo->aplicarMaterial(materialRatonEncima);

      cubo->aplicarMaterial(material3);
      cubo->aplicarColor(Tupla3f(0,0,1));
      tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
      tetraedro->aplicarMaterial(material2);
      peon->aplicarColor(Tupla3f(0,1,0));
      peon->aplicarMaterial(material1);
      cono->aplicarColor(Tupla3f(0,1,0));
      cono->aplicarMaterial(material2);
      cilindro->aplicarColor(Tupla3f(0,1,0));
      cilindro->aplicarMaterial(material3);
      esfera->aplicarColor(Tupla3f(0,1,0));
      esfera->aplicarMaterial(material3);
      muro->aplicarColor(Tupla3f(0,1,1));
      muro->aplicarMaterial(material1);
      ventana->aplicarColor(Tupla3f(0,0.2,0));
      ventana->aplicarMaterial(material1);
      robot->aplicarColor(Tupla3f(0,1,0));
      robot->aplicarMaterialTotal(material1);
    break;
    case 8:
      ventana->aplicarColor(colorRatonEncima);
      ventana->aplicarMaterial(materialRatonEncima);

      cubo->aplicarMaterial(material3);
      cubo->aplicarColor(Tupla3f(0,0,1));
      tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
      tetraedro->aplicarMaterial(material2);
      peon->aplicarColor(Tupla3f(0,1,0));
      peon->aplicarMaterial(material1);
      cono->aplicarColor(Tupla3f(0,1,0));
      cono->aplicarMaterial(material2);
      cilindro->aplicarColor(Tupla3f(0,1,0));
      cilindro->aplicarMaterial(material3);
      esfera->aplicarColor(Tupla3f(0,1,0));
      esfera->aplicarMaterial(material3);
      muro->aplicarColor(Tupla3f(0,1,1));
      muro->aplicarMaterial(material1);
      suelo->aplicarColor(Tupla3f(0,0,0.2));
      suelo->aplicarMaterial(material1);
      robot->aplicarColor(Tupla3f(0,1,0));
      robot->aplicarMaterialTotal(material1);
    break;
    case 9:
      robot->aplicarColor(colorRatonEncima);
      robot->aplicarMaterialTotal(materialRatonEncima);

      cubo->aplicarMaterial(material3);
      cubo->aplicarColor(Tupla3f(0,0,1));
      tetraedro->aplicarColor(Tupla3f(0.2,0.2,0));
      tetraedro->aplicarMaterial(material2);
      peon->aplicarColor(Tupla3f(0,1,0));
      peon->aplicarMaterial(material1);
      cono->aplicarColor(Tupla3f(0,1,0));
      cono->aplicarMaterial(material2);
      cilindro->aplicarColor(Tupla3f(0,1,0));
      cilindro->aplicarMaterial(material3);
      esfera->aplicarColor(Tupla3f(0,1,0));
      esfera->aplicarMaterial(material3);
      muro->aplicarColor(Tupla3f(0,1,1));
      muro->aplicarMaterial(material1);
      suelo->aplicarColor(Tupla3f(0,0,0.2));
      suelo->aplicarMaterial(material1);
      ventana->aplicarColor(Tupla3f(0,0.2,0));
      ventana->aplicarMaterial(material1);

    break;
  }
}
}
