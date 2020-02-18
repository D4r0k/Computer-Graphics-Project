#include "aux.h"
#include "malla.h"
#include "habitacion.h"

Habitacion::Habitacion()
{



  Tupla3f v0(0.0,0.0,170.0);
  Tupla3f v1(170.0,0.0,170.0), v2(0.0,70.0,170.0), v3(170.0,70.0,170.0);
  Tupla3f v4(0.0,0.0,0.0), v5(170.0,0.0,0.0), v6(0.0,70.0,0.0);
  Tupla3f v7(170.0,70.0,0.0);

  v.push_back(v0); //0
  v.push_back(v1); //1
  v.push_back(v2); //2
  v.push_back(v3); //3
  v.push_back(v4); //4
  v.push_back(v5); //5
  v.push_back(v6); //6
  v.push_back(v7); //7



  Tupla3i a1(0,2,1);    
  Tupla3i a2(1,2,3);
  Tupla3i c1(1,3,7);    
  Tupla3i c2(1,7,5);
  Tupla3i d1(6,4,7);  
  Tupla3i d2(7,4,5);
  Tupla3i f1(2,4,6);    
  Tupla3i f2(0,4,2);
  f.push_back(a1);
  f.push_back(a2);
  f.push_back(c1);
  f.push_back(c2);
  f.push_back(d1);
  f.push_back(d2);
  f.push_back(f1);
  f.push_back(f2);
}
