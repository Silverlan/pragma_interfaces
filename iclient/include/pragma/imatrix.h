#ifndef __IMATRIX_H__
#define __IMATRIX_H__

#include "iclientmodule.h"
#include <memory>

#pragma pack(push,1)
class DLLICLIENT IMat4
{
public:
	IMat4(
		float x0,float x1,float x2,float x3,
		float y0,float y1,float y2,float y3,
		float z0,float z1,float z2,float z3,
		float w0,float w1,float w2,float w3
	);
	IMat4();
	float m[4][4];
};
#pragma pack(pop)

#endif
