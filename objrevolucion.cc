#include "aux.h"
#include "objrevolucion.h"
#include "objply.h"
#include "ply_reader.h"





ObjRevolucion::ObjRevolucion() {

}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   std::vector<Tupla3f> perfil_original;

   ply::read_vertices(archivo, perfil_original);
   crearMalla(perfil_original, num_instancias, tapa_inf, tapa_sup);
}




ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> perfil, int num_instancias, bool tapa_sup, bool tapa_inf) {
	this->v = perfil;
	crearMalla(this->v,num_instancias, tapa_sup, tapa_inf);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_sup, bool tapa_inf) {
  //vertices
	Tupla3f color2(0.0,58.0,0.0);
   Tupla3f color1(0.0,0.25,0.54);
	float x,y,z;
   int a,b;
   numero_instancias = num_instancias;

	 Tupla3f tapainf, tapasup;

      if(perfil_original[0](0) == 0 && perfil_original[0](2) == 0 ){
         tapainf = perfil_original[0];
         perfil_original.erase(perfil_original.begin());
      }else{
         tapainf = Tupla3f(0 , perfil_original[0](1), 0);
      }

      if(perfil_original[perfil_original.size()-1](0) == 0 && perfil_original[perfil_original.size()-1](2) == 0 ){
         tapasup = perfil_original[perfil_original.size()-1];
         perfil_original.pop_back();
      }else{
         tapasup = Tupla3f(0, perfil_original[perfil_original.size()-1](1), 0);
      }

 for(int i = 0; i < num_instancias; ++i){
         for(int j = 0; j < perfil_original.size(); ++j){
            x = (perfil_original[j](0) * cos(2*M_PI * i / num_instancias)) + (perfil_original[j](2) * sin(2*M_PI * i / num_instancias));
            y = perfil_original[j](1);
            z = (perfil_original[j](0) * (- sin(2*M_PI * i / num_instancias))) + (perfil_original[j](2) * cos(2*M_PI * i / num_instancias));
            this->v.push_back(Tupla3f(x, y, z));
         }
      }


      for(int i = 0; i < num_instancias; ++i){
         for(int j = 0; j < perfil_original.size()-1; ++j){
            a = perfil_original.size()*i + j;
            b = perfil_original.size() * ((i+1) % num_instancias) + j;
            this->f.push_back(Tupla3i(a, b, b+1));
            this->f.push_back(Tupla3i(a, b+1, a+1));
            numeroT++;
         }
      }


      if(tapa_inf){
         v.push_back(tapainf);

         for(int i = 0; i < num_instancias - 1; ++i){
               f.push_back(Tupla3i(v.size() - 1, perfil_original.size() * (i+1), perfil_original.size() * i));
         }

         Tupla3i carafinal(v.size()-1, 0, perfil_original.size() * (num_instancias - 1));
         this->f.push_back(carafinal);
      }


      if(tapa_sup){
         v.push_back(tapasup);

         for(int i = 0; i < num_instancias - 1; ++i){
               f.push_back(Tupla3i(v.size() - 1, perfil_original.size() * (i+1) - 1, perfil_original.size() * (i+2) - 1));
         }
         Tupla3i carafinal(v.size()-1, v.size() - 3, perfil_original.size() - 1);
         this->f.push_back(carafinal);
      }

   }

   void ObjRevolucion::draw(int opcion, std::vector<bool> edicion, bool tapas){

	if(tapas){
      numeroT = f.size()*3;
   }else{
      numeroT = f.size()*3 - 3*2*numero_instancias;
   }

  switch(opcion){
		case 1:
			draw_ModoInmediato(edicion);
		break;
		case 2:
			draw_ModoDiferido(edicion);
		break;
      case 3:
         draw_ModoAjedrez();
      break;
   }


   }
