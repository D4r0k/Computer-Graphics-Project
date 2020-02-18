
#ifndef OBJPLY_H_INCLUDED
#define OBJPLY_H_INCLUDED

#include "aux.h"
#include "ply_reader.h"
#include "malla.h"

class ObjPLY: public Malla3D {
public:
 ObjPLY( const std::string & nombre_archivo ) ;

};

#endif
