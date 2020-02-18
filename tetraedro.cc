#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro()
{

   // inicializar la tabla de vértices



  Tupla3f v000(0.0,0.0,0.0), v001(0.0,0.0,20.0), v010(17.32,0.0,10.0);
  Tupla3f v111(5.772,17.32,10.0);

  v.push_back(v001); //2
  v.push_back(v111);
  v.push_back(v000); //0 (rojo,verde,azul)
  v.push_back(v010); //1

  Tupla3i base(0,1,2);
  Tupla3i a(0,2,3);
  Tupla3i b(0,3,1);
  Tupla3i c(1,3,2);

  f.push_back(base);
  f.push_back(a);
  f.push_back(b);
  f.push_back(c);
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

}
