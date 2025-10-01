// SPDX-FileCopyrightText: (c) 2019 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

module;

#include "definitions.hpp"
#include <cinttypes>
#include <string>
#include <sharedutils/functioncallback.h>

export module pragma.ishared:core;

export namespace ishared {
	enum class Callback : uint32_t { Think = 0 };
	DLLISHARED void add_callback(lua_State *l, Callback cb, const CallbackHandle &f);
	DLLISHARED bool protected_lua_call(lua_State *l, int nargs = 0, int nresults = 0);
	DLLISHARED bool validate_file_write_operation(lua_State *l, std::string &path);
	DLLISHARED bool load_documentation_file(const std::string &fileName);
};
