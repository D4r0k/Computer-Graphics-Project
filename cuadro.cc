#include "aux.h"
#include "malla.h"
#include "cuadro.h"

Cuadro::Cuadro()
{

  Tupla3f v0(0.0,0.0,0.0);
  Tupla3f v2(0.0,20.0,0.0), v3(20.0,20.0,0.0), v1(20.0,0.0,0.0);

  v.push_back(v0); //0
  v.push_back(v1); //1
  v.push_back(v2); //2
  v.push_back(v3); //3


  Tupla3i a1(2,0,1);
  Tupla3i a2(1,3,2);

  f.push_back(a1);
  f.push_back(a2);

  Tupla2f c_0(0.0,0.0);
  Tupla2f c_1(0.0,1.0);
  Tupla2f c_2(1.0,0);
  Tupla2f c_3(1,1);

  ct.push_back(c_1);
  ct.push_back(c_3);
  ct.push_back(c_0);
  ct.push_back(c_2);


}
