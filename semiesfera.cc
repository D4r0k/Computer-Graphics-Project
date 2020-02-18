#include "aux.h"
#include "malla.h"
#include "semiesfera.h"



Semiesfera::Semiesfera(int num_vert_perfil, int num_instancias, float r){
  radio = r;
  std::vector<Tupla3f> perfil;
  Tupla3f vertice_inicial(0.0, -radio, 0.0);
  Tupla3f vertice_final(0.0, radio, 0.0);
  float x,y;
  
  //perfil.push_back(vertice_inicial);

  for(int i=num_vert_perfil/2; i<num_vert_perfil; i++){
		x = sin(M_PI * i/num_vert_perfil)*(-radio);
		y = cos(M_PI * i/num_vert_perfil)*(-radio);
    Tupla3f vertice(x,y,0);
    perfil.push_back(vertice);
  }

  perfil.push_back(vertice_final);


  crearMalla(perfil,num_instancias,true,true);
}
