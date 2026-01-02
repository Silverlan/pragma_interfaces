// SPDX-FileCopyrightText: (c) 2019 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

module pragma.iclient;

import :vector;

IVector3::IVector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
IVector3::IVector3() : IVector3(0.f, 0.f, 0.f) {}
