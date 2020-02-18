#include "aux.h"
#include "malla.h"
#include "cono.h"

Cono::Cono(int num_vert_perfil, int num_instancias, float h, float r, bool tapa_sup, bool tapa_inf){
  num_vert_perfil = 1;
  this->altura = h;
  this->radio = r;
  std::vector<Tupla3f> perfil;

  perfil.push_back(Tupla3f(0, 0, 0));

  perfil.push_back(Tupla3f(0, 0, r));
  
  perfil.push_back(Tupla3f(0, h, 0));

  crearMalla(perfil, num_instancias, tapa_inf, tapa_sup);
}
