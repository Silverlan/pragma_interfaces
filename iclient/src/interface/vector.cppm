// SPDX-FileCopyrightText: (c) 2019 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

module;

#include "iclient_definitions.hpp"
#include <memory>

export module pragma.iclient:vector;

#pragma pack(push, 1)
export class DLLICLIENT IVector3 {
  public:
	IVector3(float x, float y, float z);
	IVector3();
	float x;
	float y;
	float z;
};
#pragma pack(pop)
