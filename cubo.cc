#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

  Tupla3f v0(0.0,0.0,20.0);
  Tupla3f v1(20.0,0.0,20.0), v2(0.0,20.0,20.0), v3(20.0,20.0,20.0);
  Tupla3f v4(0.0,0.0,0.0), v5(20.0,0.0,0.0), v6(0.0,20.0,0.0);
  Tupla3f v7(20.0,20.0,0.0);

  v.push_back(v0); 
  v.push_back(v1); 
  v.push_back(v2);
  v.push_back(v3); 
  v.push_back(v4); 
  v.push_back(v5); 
  v.push_back(v6); 
  v.push_back(v7); 



  Tupla3i a1(0,1,2);
  Tupla3i a2(1,3,2);
  Tupla3i b1(2,3,7);
  Tupla3i b2(2,7,6);
  Tupla3i c1(1,7,3);
  Tupla3i c2(1,5,7);
  Tupla3i d1(6,7,4);
  Tupla3i d2(7,5,4);
  Tupla3i e1(0,4,1);
  Tupla3i e2(1,4,5);
  Tupla3i f1(2,6,4);
  Tupla3i f2(0,2,4);

  f.push_back(a1);
  f.push_back(a2);
  f.push_back(b1);
  f.push_back(b2);
  f.push_back(c1);
  f.push_back(c2);
  f.push_back(d1);
  f.push_back(d2);
  f.push_back(e1);
  f.push_back(e2);
  f.push_back(f1);
  f.push_back(f2);


}
