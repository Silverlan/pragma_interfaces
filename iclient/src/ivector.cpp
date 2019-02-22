#include "pragma/ivector.h"

IVector3::IVector3(float _x,float _y,float _z)
	: x(_x),y(_y),z(_z)
{}
IVector3::IVector3()
	: IVector3(0.f,0.f,0.f)
{}
