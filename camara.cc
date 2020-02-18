#include "camara.h"
#include "aux.h"
#include "tuplasg.h"

Camara::Camara(Tupla3f eye, Tupla3f at, Tupla3f up, int tipo, float left, float right, float top, float bottom, float near, float far){
	this->eye = eye;
	this->at = at;
	this->up = up;
	this->tipo = tipo;
	this->left = left;
	this->right = right;
	this->bottom = bottom;
	this->top = top;
	this->near = near;
	this->far = far;

	vector_n = {0,0,0};
	vector_u = {0,0,0};
	vector_v = {0,0,0};
	valor_n = 0;
	valor_u = 0;
	valor_v = 0;
	valor_aux = 0;	
}

void Camara::calcularVectores(){
	
	//Vector VPN
	vector_n = eye - at;
	valor_n = sqrt(vector_n[0]*vector_n[0] + vector_n[1]*vector_n[1] + vector_n[2]*vector_n[2]);
	vector_n = {vector_n[0]/valor_n, vector_n[1]/valor_n, vector_n[2]/valor_n};

	//Vector U (Perpendicular a VUPxVPN)
	up = up - at;
	vector_u = up.cross(vector_n);
	valor_u = sqrt(vector_u[0]*vector_u[0] + vector_u[1]*vector_u[1] + vector_u[2]*vector_u[2]);
	vector_u = {vector_u[0]/valor_u, vector_u[1]/valor_u, vector_u[2]/valor_u};

	//Vector Y Ortogonal a N y U
	vector_v= vector_n.cross(vector_u);
	valor_v = sqrt(vector_v[0]*vector_v[0] + vector_v[1]*vector_v[1] + vector_v[2]*vector_v[2]);
	vector_v = {vector_v[0]/valor_v, vector_v[1]/valor_v, vector_v[2]/valor_v};

    valor_aux = vector_u.dot(vector_v.cross(vector_n)) ;

}

void Camara::calcularEye(){
	float x,y,z;
	x = eye[0]*vector_u[0] + eye[1]*vector_v[0] + eye[2]*vector_n[0] ;
    y = eye[0]*vector_u[1] + eye[1]*vector_v[1] + eye[2]*vector_n[1] ;
    z = eye[0]*vector_u[2] + eye[1]*vector_v[2] + eye[2]*vector_n[2] ;
	eye = {x/valor_aux, y/valor_aux, z/valor_aux};
}

void Camara::calcularUp(){
	float x,y,z,up_aux;
	x = up[0]*vector_u[0] + up[1]*vector_v[0] + up[2]*vector_n[0] ;
    y = up[0]*vector_u[1] + up[1]*vector_v[1] + up[2]*vector_n[1] ;
    z = up[0]*vector_u[2] + up[1]*vector_v[2] + up[2]*vector_n[2] ;

	up_aux = sqrt(x*x + y*y + z*z);
	up = {x/valor_aux/up_aux, y/valor_aux/up_aux, z/up_aux};
}


void Camara::rotarXExaminar(float angle){

	calcularVectores();

	eye = {eye.dot(vector_u), eye.dot(vector_v), eye.dot(vector_n)};
	eye = {(float)cos(angle*PI/180)*eye[0] - (float)sin(angle*PI/180)*eye[2], eye[1], (float)sin(angle*PI/180)*eye[0] + (float)cos(angle*PI/180)*eye[2]};
	calcularEye();


	up = {up.dot(vector_u), up.dot(vector_v), up.dot(vector_n)};
	up = {(float)cos(angle*PI/180)*up[0] - (float)sin(angle*PI/180)*up[2], up[1], (float)sin(angle*PI/180)*up[0] + (float)cos(angle*PI/180)*up[2]};
	calcularUp();
}

void Camara::rotarYExaminar(float angle){

	calcularVectores();

	eye = {eye.dot(vector_u), eye.dot(vector_v), eye.dot(vector_n)};
	eye = {eye[0], (float)cos(angle*PI/180)*eye[1] - (float)sin(angle*PI/180)*eye[2] , (float)sin(angle*PI/180)*eye[1] + (float)cos(angle*PI/180)*eye[2]};
    calcularEye();

	up = {up.dot(vector_u), up.dot(vector_v), up.dot(vector_n)};
	up = {up[0], (float)cos(angle*PI/180)*up[1] - (float)sin(angle*PI/180)*up[2] , (float)sin(angle*PI/180)*up[1] + (float)cos(angle*PI/180)*up[2]};
    calcularUp();

}

void Camara::zoom (float factor){
	left *= factor ;
	right *= factor ;
	top *= factor ;
	bottom *= factor ;

}

void Camara::setObserver(){
	gluLookAt(eye(0),eye(1),eye(2),at(0),at(1),at(2),up(0),up(1),up(2));
}


void Camara::setProyeccion(){
	if (tipo == 0){
        glFrustum(left, right, bottom, top, near, far);
    }else if(tipo == 1	){
        glOrtho(left, right, bottom, top, near, far);
    }

}

void Camara::setObjetivo(float x, float y, float z){
	Tupla3f objetivo = {x,y,z};
	at = objetivo;
}
