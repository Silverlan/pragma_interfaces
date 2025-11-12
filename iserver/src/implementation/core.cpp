// SPDX-FileCopyrightText: (c) 2019 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

module;

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#endif

module pragma.iserver;

import :core;
import pragma.server;

// import pragma.scripting.lua;

static ServerState *sv() {return dynamic_cast<ServerState*>(pragma::get_server_state());}
static SGame *sg() {return sv()->GetGameState();}

static void add_server_callback(const std::string &identifier, const CallbackHandle &callback) { sv()->AddCallback(identifier, callback); }

static void add_game_callback(const std::string &identifier, const CallbackHandle &callback)
{
    auto *game = sg();
	if(game == nullptr)
		return;
	game->AddCallback(identifier, callback);
}

void iserver::add_callback(Callback cb, const CallbackHandle &f)
{
	switch(cb) {
	case Callback::Think:
		sv()->AddThinkCallback(f);
		break;
	case Callback::OnLuaInitialized:
		add_game_callback("OnLuaInitialized", f);
		break;
	case Callback::OnGameStart:
		sv()->AddCallback("OnGameStart", f);
		break;
	case Callback::EndGame:
		sv()->AddCallback("EndGame", f);
		break;
	case Callback::OnGameInitialized:
		add_game_callback("OnGameInitialized", f);
		break;
	};
}

bool iserver::is_game_active() { return sv()->IsGameActive(); }
bool iserver::is_game_initialized() { return is_game_active() && sv()->GetGameState()->IsGameInitialized(); }

std::shared_ptr<pragma::Model> iserver::create_model(bool bAddReference) { return sg()->CreateModel(bAddReference); }

lua::State *iserver::get_lua_state() { return sv()->GetLuaState(); }

double iserver::real_time() { return sv()->RealTime(); }
double iserver::delta_time() { return sv()->DeltaTime(); }
double iserver::last_think() { return sv()->LastThink(); }

bool iserver::protected_lua_call(int nargs, int nresults)
{
	auto *l = sv()->GetLuaState();
	return pragma::scripting::lua_core::protected_call(l, nargs, nresults) == Lua::StatusCode::Ok;
}
