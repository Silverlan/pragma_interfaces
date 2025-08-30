// SPDX-FileCopyrightText: (c) 2019 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

module;

#include "iclient_definitions.hpp"
#include <memory>

export module pragma.iclient:matrix;

#pragma pack(push, 1)
export class DLLICLIENT IMat4 {
  public:
	IMat4(float x0, float x1, float x2, float x3, float y0, float y1, float y2, float y3, float z0, float z1, float z2, float z3, float w0, float w1, float w2, float w3);
	IMat4();
	float m[4][4];
};
#pragma pack(pop)
