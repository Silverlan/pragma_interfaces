#include "pragma/imatrix.h"

IMat4::IMat4(
	float x0,float x1,float x2,float x3,
	float y0,float y1,float y2,float y3,
	float z0,float z1,float z2,float z3,
	float w0,float w1,float w2,float w3
)
	: m{
		{x0,x1,x2,x3},
		{y0,y1,y2,y3},
		{z0,z1,z2,z3},
		{w0,w1,w2,w3},
	}
{}
IMat4::IMat4()
	: IMat4(
		1.f,0.f,0.f,0.f,
		0.f,1.f,0.f,0.f,
		0.f,0.f,1.f,0.f,
		0.f,0.f,0.f,1.f
	)
{}