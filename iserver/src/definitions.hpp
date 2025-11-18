// SPDX-FileCopyrightText: (c) 2019 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

#ifndef __ISERVER_DEFINITIONS_HPP__
#define __ISERVER_DEFINITIONS_HPP__

#ifdef DLLISERVER_EX
#ifdef __linux__
#define DLLISERVER __attribute__((visibility("default")))
#else
#define DLLISERVER __declspec(dllexport)
#endif
#else
#ifdef __linux__
#define DLLISERVER
#else
#define DLLISERVER __declspec(dllimport)
#endif
#endif

#endif
