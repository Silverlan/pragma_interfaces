// SPDX-FileCopyrightText: (c) 2019 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

#include "pragma/ishared.hpp"
#include <pragma/level/mapinfo.h>
#include <pragma/lua/libraries/lfile.h>
#include <pragma/engine.h>
#include <pragma/lua/lua_doc.hpp>
#include <pragma/networkstate/networkstate.h>
#include <pragma/lua/libraries/lfile.h>
#include <pragma/lua/ldefinitions.h>

extern DLLNETWORK Engine *engine;

void ishared::add_callback(lua_State *l, Callback cb, const CallbackHandle &f)
{
	auto *nw = engine->GetNetworkState(l);
	if(nw == nullptr)
		return;
	switch(cb) {
	case Callback::Think:
		nw->AddThinkCallback(f);
		break;
	};
}

bool ishared::protected_lua_call(lua_State *l, int nargs, int nresults)
{
	auto err = Lua::ProtectedCall(l, nargs, nresults);
	if(err == Lua::StatusCode::Ok)
		return true;
	Lua::HandleLuaError(l, err);
	return false;
}

bool ishared::validate_file_write_operation(lua_State *l, std::string &path) { return Lua::file::validate_write_operation(l, path); }

bool ishared::load_documentation_file(const std::string &fileName) { return Lua::doc::load_documentation_file(fileName); }
