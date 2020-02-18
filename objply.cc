#include "objply.h"
#include "ply_reader.h"

using namespace std;

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   ply::read( nombre_archivo, this->v, this->f);
}

