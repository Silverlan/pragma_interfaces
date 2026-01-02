// SPDX-FileCopyrightText: (c) 2019 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

module;

#include <cinttypes>
#include <string>

export module pragma.ishared:core;

export import pragma.lua;

export namespace ishared {
	enum class Callback : uint32_t { Think = 0 };
	DLLISHARED void add_callback(lua::State *l, Callback cb, const CallbackHandle &f);
	DLLISHARED bool protected_lua_call(lua::State *l, int nargs = 0, int nresults = 0);
	DLLISHARED bool validate_file_write_operation(lua::State *l, std::string &path);
	DLLISHARED bool load_documentation_file(const std::string &fileName);
};
