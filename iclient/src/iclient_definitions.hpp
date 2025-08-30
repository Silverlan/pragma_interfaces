// SPDX-FileCopyrightText: (c) 2019 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

#ifndef __ICLIENT_DEFINITIONS_HPP__
#define __ICLIENT_DEFINITIONS_HPP__

#ifdef DLLICLIENT_EX
#ifdef __linux__
#define DLLICLIENT __attribute__((visibility("default")))
#else
#define DLLICLIENT __declspec(dllexport)
#endif
#else
#ifdef __linux__
#define DLLICLIENT
#else
#define DLLICLIENT __declspec(dllimport)
#endif
#endif

#endif
