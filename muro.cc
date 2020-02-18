#include "aux.h"
#include "malla.h"
#include "muro.h"

Muro::Muro()
{


  Tupla3f v4(0.0,0.0,0.0), v5(160.0,0.0,0.0), v6(0.0,80.0,0.0);
  Tupla3f v7(160.0,80.0,0.0);


  v.push_back(v4); //4
  v.push_back(v5); //5
  v.push_back(v6); //6
  v.push_back(v7); //7



  Tupla3i a1(2,0,1);    
  Tupla3i a2(1,3,2);


  f.push_back(a1);
  f.push_back(a2);

  Tupla2f c_0(0.0,0.0);
  Tupla2f c_1(1,0.0);
  Tupla2f c_2(0.0,1);
  Tupla2f c_3(1,1);

  ct.push_back(c_0);
  ct.push_back(c_1);
  ct.push_back(c_2);
  ct.push_back(c_3);



}
