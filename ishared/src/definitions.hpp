// SPDX-FileCopyrightText: (c) 2019 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

#ifndef __ISHARED_DEFINITIONS_HPP__
#define __ISHARED_DEFINITIONS_HPP__

#ifdef DLLISHARED_EX
#ifdef __linux__
#define DLLISHARED __attribute__((visibility("default")))
#else
#define DLLISHARED __declspec(dllexport) // export DLL information
#endif
#else
#ifdef __linux__
#define DLLISHARED
#else
#define DLLISHARED __declspec(dllimport) // import DLL information
#endif
#endif

#endif
