#ifndef AUX_H_INCLUDED
#define AUX_H_INCLUDED

#ifdef _WIN32
#  include <windows.h>
#endif

#include <cmath>    
#include <cstdlib>  
#include <ostream> 
#include <string>   
#include <vector>   

#ifdef LINUX
#  include <GL/glew.h> 
#  include <GL/glut.h> 
#  include <GL/glu.h>
#endif

#ifdef MACOS
#  include <OpenGL/GL.h>
#  include <OpenGL/glu.h>   
#  include <GLUT/glut.h>    
#  pragma GCC diagnostic ignored "-Wdeprecated-declarations" 
#endif

#include "tuplasg.h" 


#endif 
