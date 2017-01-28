#ifndef _VERTEX_TYPE_CH
#define _VERTEX_TYPE_CH


struct CVertex_fXYZW
{
	CVertex_fXYZW() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}; 
	float x, y, z, w;
};


#endif