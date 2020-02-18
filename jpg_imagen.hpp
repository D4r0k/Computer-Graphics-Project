#ifndef JPG_IMAGEN_HPP
#define JPG_IMAGEN_HPP

#include <string>


namespace jpg 
{

class Imagen 
{
	public:


	Imagen( const std::string & nombreArchivo ) ;


	Imagen( const std::wstring & wstr ) ;


	unsigned char * leerPixels()  ;


	unsigned char * leerPixel( unsigned ix, unsigned iy ) ;
	unsigned long tamX() const ;

	// devuelve el numero de filas de la imagen
	unsigned long tamY() const ;

	// intenta escribir la imagen en un archivo JPG
	void escribirEn( const std::string & nombreArchivo );
	
	// borra el buffer
	~Imagen () ;

	private:
    
   unsigned char * buf  ;  // buffer con los pixel
	unsigned int    w, h ;  // ancho y alto, respectivamente

} ;

}

#endif
