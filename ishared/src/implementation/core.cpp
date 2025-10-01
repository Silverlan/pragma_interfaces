// SPDX-FileCopyrightText: (c) 2019 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

module;

module pragma.ishared;

import :core;

// import pragma.scripting.lua;

void ishared::add_callback(lua_State *l, Callback cb, const CallbackHandle &f)
{
	auto *nw = Engine::Get()->GetNetworkState(l);
	if(nw == nullptr)
		return;
	switch(cb) {
	case Callback::Think:
		nw->AddThinkCallback(f);
		break;
	};
}

bool ishared::protected_lua_call(lua_State *l, int nargs, int nresults) { return pragma::scripting::lua::protected_call(l, nargs, nresults) == Lua::StatusCode::Ok; }

bool ishared::validate_file_write_operation(lua_State *l, std::string &path) { return Lua::file::validate_write_operation(l, path); }

bool ishared::load_documentation_file(const std::string &fileName) { return Lua::doc::load_documentation_file(fileName); }
