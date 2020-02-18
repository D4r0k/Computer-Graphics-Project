// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"
#include "textura.h"
// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:

   GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram);

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato( std::vector<bool> edicion);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(std::vector<bool> edicion);
   void draw_ModoAjedrez();

   void draw_ModoPuntos();
   void draw_ModoLineas();
   void draw_ModoSolido();
   void drawSimple();
   void calcularNormales();
   void aplicarMaterial(Material *& material);
   void aplicarTextura(Textura *& textura);
   void aplicarColor(Tupla3f color);
   void aplicarColorSeleccion(Tupla3f color);


   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(int opcion, std::vector<bool> edicion) ;

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3f> c1 ;
   std::vector<Tupla3f> c2 ; //Vector de colores
   std::vector<Tupla3f> nv ; //Vector de normales
   std::vector<Tupla2f> ct;
   std::vector<Tupla3f> coloresSeleccion;
   Textura *textura = nullptr;
   GLuint id_vbo_ver=0;
   GLuint id_vbo_tri=0;
   GLuint id_vbo_normales=0;
   GLuint id_vbo_colores=0;
   Material * material = nullptr;
   int numeroT = 0;

   // completar: tabla de colores, tabla de normales de vértices
} ;


#endif
