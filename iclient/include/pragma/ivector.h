// SPDX-FileCopyrightText: (c) 2019 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

#ifndef __IVECTOR_H__
#define __IVECTOR_H__

#include "iclientmodule.h"
#include <memory>

#pragma pack(push, 1)
class DLLICLIENT IVector3 {
  public:
	IVector3(float x, float y, float z);
	IVector3();
	float x;
	float y;
	float z;
};
#pragma pack(pop)

#endif
