#ifndef __ISERVER_H__
#define __ISERVER_H__

#define NULL 0

extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#include <string>
#include <memory>

#ifdef DLLISERVER_EX
	#define DLLISERVER __declspec(dllexport)
#else
	#define DLLISERVER __declspec(dllimport)
#endif

extern class __declspec(dllimport) WILuaHandleWrapper;
extern class __declspec(dllimport) WIHandle;
extern class CallbackHandle;
class Model;
namespace iserver
{
	enum class DLLISERVER Callback : uint32_t
	{
		Think = 0,
		OnLuaInitialized,
		OnGameStart,
		EndGame,
		OnGameInitialized
	};
	DLLISERVER void add_callback(Callback cb,const CallbackHandle &f);
	DLLISERVER lua_State *get_lua_state();
	DLLISERVER double real_time();
	DLLISERVER double delta_time();
	DLLISERVER double last_think();
	DLLISERVER bool protected_lua_call(int nargs=0,int nresults=0);
	DLLISERVER bool is_game_active();
	DLLISERVER std::shared_ptr<::Model> create_model(bool bAddReference=true);
	DLLISERVER bool is_game_initialized();
};

#endif