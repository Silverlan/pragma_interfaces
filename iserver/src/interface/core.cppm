// SPDX-FileCopyrightText: (c) 2019 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

export module pragma.iserver:core;

export import pragma.lua;
import pragma.shared;

export namespace iserver {
	enum class Callback : uint32_t { Think = 0, OnLuaInitialized, OnGameStart, EndGame, OnGameInitialized };
	DLLISERVER void add_callback(Callback cb, const CallbackHandle &f);
	DLLISERVER lua::State *get_lua_state();
	DLLISERVER double real_time();
	DLLISERVER double delta_time();
	DLLISERVER double last_think();
	DLLISERVER bool protected_lua_call(int nargs = 0, int nresults = 0);
	DLLISERVER bool is_game_active();
	DLLISERVER std::shared_ptr<pragma::asset::Model> create_model(bool bAddReference = true);
	DLLISERVER bool is_game_initialized();
};
