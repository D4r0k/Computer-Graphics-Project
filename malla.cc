#include "aux.h"
#include "malla.h"

using namespace std;
// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//

// -----------------------------------------------------------------------------
// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato(std::vector<bool> edicion)
{
  glShadeModel(GL_SMOOTH);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer( 3,GL_FLOAT, 0, v.data() ) ;

  if(edicion[0]){
    glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
    glPointSize(2);
    glEnableClientState( GL_COLOR_ARRAY );
    glColorPointer(3,GL_FLOAT,0,c2.data());
    glDrawElements(GL_TRIANGLES,numeroT,GL_UNSIGNED_INT,f.data() );
    glDisableClientState( GL_COLOR_ARRAY );

  }
  if(edicion[1]){
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glLineWidth(1);
    glEnableClientState( GL_COLOR_ARRAY );
    glColorPointer(3,GL_FLOAT,0,c2.data());
    glDrawElements(GL_TRIANGLES,numeroT,GL_UNSIGNED_INT,f.data() );
    glDisableClientState( GL_COLOR_ARRAY );

  }
  if(edicion[2]){
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glEnableClientState( GL_COLOR_ARRAY );
    glColorPointer(3,GL_FLOAT,0,c1.data());
    glDrawElements(GL_TRIANGLES,numeroT,GL_UNSIGNED_INT,f.data() );
    glDisableClientState( GL_COLOR_ARRAY );
  }
  if(edicion[3]){
    material->aplicar();
        if(nv.size() == 0){   //Si el vector de las normales está vacío que calcule las normales
            calcularNormales();
        }
    glEnable(GL_NORMALIZE);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, v.data());
		glNormalPointer(GL_FLOAT, 0, nv.data());
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES,numeroT, GL_UNSIGNED_INT, f.data());
		glDisableClientState(GL_NORMAL_ARRAY);
  }


  glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

GLuint Malla3D::CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram){

  GLuint id_vbo; //resultado: identificador de VBO
  glGenBuffers(1,&id_vbo); //crear nuevo VBO, obtener identificador (nunca 0)
  glBindBuffer(tipo_vbo,id_vbo); //activar el VBO usando su identificador

  //esta instrucción hace la transferencia de datos desde RAM hacia GPU
  glBufferData(tipo_vbo,tamanio_bytes,puntero_ram,GL_STATIC_DRAW);
  glBindBuffer(tipo_vbo, 0 ); //desactivación del VBO (activar 0)

  return id_vbo; //devolver el identificador resultado
}

void Malla3D::draw_ModoDiferido(std::vector<bool> edicion)
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   if(id_vbo_ver == 0) //Priemra vez, lo creamos
    id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, 3*v.size()*sizeof(float),v.data());
   if(id_vbo_tri == 0)
    id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, numeroT*sizeof(unsigned int), f.data());
   if(id_vbo_normales == 0)
    id_vbo_normales = CrearVBO(GL_ARRAY_BUFFER, 3*nv.size()*sizeof(unsigned int), nv.data());
   if(id_vbo_colores == 0)
    id_vbo_colores = CrearVBO(GL_ARRAY_BUFFER, 3*c1.size()*sizeof(unsigned int), c1.data());
   // especificar localización y formato de la tabla de vértices, habilitar tabla
   glBindBuffer(GL_ARRAY_BUFFER,id_vbo_ver); //activar VBO de vértices
   glVertexPointer( 3,GL_FLOAT, 0, 0 ); //especifica formato y offset (=0)
   glBindBuffer(GL_ARRAY_BUFFER, 0 ); //desactivar VBO de vértices.
   glEnableClientState(GL_VERTEX_ARRAY); // habilitar tabla de vértices
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_vbo_tri); //activar VBO de triángulos

   if(!edicion[4]){ //Si no está iluminación activada
     glBindBuffer(GL_ARRAY_BUFFER, id_vbo_colores);
     glVertexPointer( 3,GL_FLOAT, 0, 0 ); //especifica formato y offset (=0)
     glBindBuffer(GL_ARRAY_BUFFER, 0 );
     glEnableClientState(GL_COLOR_ARRAY);
     glShadeModel(GL_FLAT);
   }

   if(edicion[0]){
     glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
     glPointSize(5);
     glEnableClientState( GL_COLOR_ARRAY );
     glColorPointer(3,GL_FLOAT,0,c2.data());
     glDrawElements(GL_TRIANGLES,numeroT,GL_UNSIGNED_INT,f.data() );
     glDisableClientState( GL_COLOR_ARRAY );

   }
   if(edicion[1]){
     glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
     glLineWidth(2);
     glEnableClientState( GL_COLOR_ARRAY );
     glColorPointer(3,GL_FLOAT,0,c2.data());
     glDrawElements(GL_TRIANGLES,numeroT,GL_UNSIGNED_INT,f.data() );
     glDisableClientState( GL_COLOR_ARRAY );

   }
   if(edicion[2]){
     glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
     glEnableClientState( GL_COLOR_ARRAY );
     glColorPointer(3,GL_FLOAT,0,c1.data());
     glDrawElements(GL_TRIANGLES,numeroT,GL_UNSIGNED_INT,f.data() );
     glDisableClientState( GL_COLOR_ARRAY );
   }
   if(edicion[3]){
     material->aplicar();
     if(nv.size() == 0){   //Si el vector de las normales está vacío que calcule las normales
             calcularNormales();
     }
    glBindBuffer(GL_ARRAY_BUFFER, id_vbo_normales);
		glNormalPointer(GL_FLOAT, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glEnableClientState(GL_NORMAL_ARRAY);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, numeroT, GL_UNSIGNED_INT, f.data());
		glDisableClientState(GL_NORMAL_ARRAY);
   }

   if(!edicion[4]){
     glDisableClientState(GL_COLOR_ARRAY);
   }

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0 ); //desactivar VBO de triángulos
   //desactivar uso de array de vértices
   glDisableClientState(GL_VERTEX_ARRAY);
}

// -----------------------------------------------------------------------------
void Malla3D::draw_ModoAjedrez()
{
  std::vector<Tupla3i> fimpares ;
  std::vector<Tupla3i> fpares ;

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glShadeModel(GL_FLAT);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer( 3,GL_FLOAT, 0, v.data() ) ;
  for (int i = 0; i < numeroT/3; i++) {
    if(i % 2 == 0){
      fpares.push_back(f.at(i));
    }else{
      fimpares.push_back(f.at(i));
    }
  }
  glEnableClientState( GL_COLOR_ARRAY );
  glColorPointer(3,GL_FLOAT,0,c1.data());
  glDrawElements(GL_TRIANGLES,fpares.size()*3,GL_UNSIGNED_INT,fpares.data());
  glDisableClientState( GL_COLOR_ARRAY );

  glEnableClientState( GL_COLOR_ARRAY );
  glColorPointer(3,GL_FLOAT,0,c2.data());
  glDrawElements(GL_TRIANGLES,fimpares.size()*3,GL_UNSIGNED_INT,fimpares.data());
  glDisableClientState( GL_COLOR_ARRAY );
  glDisableClientState(GL_VERTEX_ARRAY);


}
// -----------------------------------------------------------------------------

void Malla3D::calcularNormales()
{
  std::vector<Tupla3f> nc;  //Vector de normales de las caras
  Tupla3f v1,v2,v3;
  Tupla3f arista1,arista2;
  Tupla3f mc;

  for(int i = 0; i < v.size(); ++i){
    nv.push_back(Tupla3f(0, 0, 0));   //Lo inicializamos todo al vertice origen
  }

  for (int i = 0; i < f.size(); i++) //Para cada cara
  {
    v1 = v[f[i](0)];   //Posiciones tres vertices
    v2 = v[f[i](1)];
    v3 = v[f[i](2)];
    arista1 =v2-v1;     //calculo de las aristas
    arista2 =v3-v1;

    mc = arista1.cross(arista2);    //Perpendicular con el producto vectorial
    nc.push_back(mc.normalized());    //Conseguimos el vector normal de las caras normalizando el vector mc

    nv[f[i](0)] = nv[f[i](0)] + nc[i];
    nv[f[i](1)] = nv[f[i](1)] + nc[i];
    nv[f[i](2)] = nv[f[i](2)] + nc[i];
  }


  for (int i = 0; i < nv.size(); i++)
  {
    nv[i] = nv[i].normalized();
  }
}

void Malla3D::aplicarMaterial(Material *& material){
   this->material = material;
}

void Malla3D::aplicarTextura(Textura *& textura){
   this->textura = textura;
}

void Malla3D::aplicarColor(Tupla3f color){
  c1.clear();
  c2.clear();
  Tupla3f color2(color(0)-0.5,color(1)-0.5,color(2)-0.5);
  for(int i = 0; i<v.size(); i++){
    c1.push_back(color);
    c2.push_back(color2);
  }
}

void Malla3D::aplicarColorSeleccion(Tupla3f color){
  coloresSeleccion.clear();
  for (int i = 0; i < v.size(); i++) {
    coloresSeleccion.push_back(color);
  }
}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(int opcion,std::vector<bool> edicion)
{
  if(numeroT == 0){
    numeroT = f.size()*3;
  }

  if(nv.size() == 0){   //Si el vector de las normales está vacío que calcule las normales
    calcularNormales();
  }

  if(ct.size() > 0){
    glEnable(GL_TEXTURE_2D);

    textura->activar();
  }

  switch(opcion){
		case 1:
        glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glTexCoordPointer( 2, GL_FLOAT, 0,ct.data());
			draw_ModoInmediato(edicion);
          glDisableClientState( GL_TEXTURE_COORD_ARRAY );
			break;
		case 2:
        glEnableClientState( GL_TEXTURE_COORD_ARRAY );
        glTexCoordPointer( 2, GL_FLOAT, 0,ct.data());
			  draw_ModoDiferido(edicion);
        glDisableClientState( GL_TEXTURE_COORD_ARRAY );
			break;
    case 3:
      draw_ModoAjedrez();
    break;
    }

    glDisable(GL_TEXTURE_2D);

}

void Malla3D::drawSimple(){
   glEnableClientState(GL_VERTEX_ARRAY) ;
   glEnableClientState(GL_COLOR_ARRAY) ;
   glVertexPointer( 3,GL_FLOAT, 0, v.data() ) ;
   glColorPointer(3, GL_FLOAT, 0, coloresSeleccion.data());
   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL) ;
   glDrawElements(GL_TRIANGLES,f.size()*3,GL_UNSIGNED_INT, f.data()) ;
   glDisableClientState(GL_COLOR_ARRAY) ;
   glDisableClientState(GL_VERTEX_ARRAY) ;
}
