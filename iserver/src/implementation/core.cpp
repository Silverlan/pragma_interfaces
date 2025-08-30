// SPDX-FileCopyrightText: (c) 2019 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

module;

#ifdef _WIN32
#include <Windows.h>
#endif
#include <materialmanager.h>
#include <mathutil/eulerangles.h>
#include <sharedutils/util_cpu_profiler.hpp>
#include <pragma/serverstate/serverstate.h>
#include <scripting/lua/lua.hpp>

module pragma.iserver;

import :core;

// import pragma.scripting.lua;

extern DLLSERVER ServerState *server;
extern DLLSERVER SGame *s_game;
static void add_server_callback(const std::string &identifier, const CallbackHandle &callback) { server->AddCallback(identifier, callback); }

static void add_game_callback(const std::string &identifier, const CallbackHandle &callback)
{
	if(s_game == nullptr)
		return;
	s_game->AddCallback(identifier, callback);
}

void iserver::add_callback(Callback cb, const CallbackHandle &f)
{
	switch(cb) {
	case Callback::Think:
		server->AddThinkCallback(f);
		break;
	case Callback::OnLuaInitialized:
		add_game_callback("OnLuaInitialized", f);
		break;
	case Callback::OnGameStart:
		server->AddCallback("OnGameStart", f);
		break;
	case Callback::EndGame:
		server->AddCallback("EndGame", f);
		break;
	case Callback::OnGameInitialized:
		add_game_callback("OnGameInitialized", f);
		break;
	};
}

bool iserver::is_game_active() { return server->IsGameActive(); }
bool iserver::is_game_initialized() { return is_game_active() && server->GetGameState()->IsGameInitialized(); }

std::shared_ptr<::Model> iserver::create_model(bool bAddReference) { return s_game->CreateModel(bAddReference); }

lua_State *iserver::get_lua_state() { return server->GetLuaState(); }

double iserver::real_time() { return server->RealTime(); }
double iserver::delta_time() { return server->DeltaTime(); }
double iserver::last_think() { return server->LastThink(); }

bool iserver::protected_lua_call(int nargs, int nresults)
{
	lua_State *l = server->GetLuaState();
	return pragma::scripting::lua::protected_call(l, nargs, nresults) == Lua::StatusCode::Ok;
}
