#ifndef __ICLIENT_H__
#define __ICLIENT_H__

#define NULL 0

extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#include <string>
#include <memory>
#include <functional>
#include "iclientmodule.h"
#include <sharedutils/util_shared_handle.hpp>

class WIBase;
using WIHandle = util::TWeakSharedHandle<WIBase>;
extern class CallbackHandle;
struct GLFWwindow;
class IScene;
class Model;
class WIBase;
namespace prosper {class RenderTarget; class IPrContext; class Shader; class IPrimaryCommandBuffer; class Texture;};
namespace luabind {namespace adl{class object;};};
namespace iclient
{
	enum class Callback : uint32_t
	{
		Think = 0,
		Draw,
		DrawScene,
		OnLuaInitialized,
		OnGameStart,
		EndGame,
		OnGameInitialized,
		PreRender,
		PostRender,
		EngineDraw
	};
	DLLICLIENT const CallbackHandle &add_callback(Callback cb,const CallbackHandle &f);
	DLLICLIENT lua_State *get_lua_state();
	DLLICLIENT lua_State *get_gui_lua_state();
	DLLICLIENT void add_gui_lua_wrapper_factory(const std::function<luabind::adl::object(lua_State*,WIBase&)> &f);
	DLLICLIENT double real_time();
	DLLICLIENT double delta_time();
	DLLICLIENT double last_think();
	DLLICLIENT bool protected_lua_call(int nargs=0,int nresults=0);
	DLLICLIENT GLFWwindow *get_context_window();
	DLLICLIENT std::shared_ptr<prosper::Texture> get_presentation_texture();
	DLLICLIENT IScene get_render_scene();
	DLLICLIENT IScene get_main_scene();
	DLLICLIENT const prosper::IPrContext &get_render_context();
	DLLICLIENT void draw_scene(const IScene &cam,const std::shared_ptr<prosper::IPrimaryCommandBuffer> &drawCmd,std::shared_ptr<prosper::RenderTarget> &rt);
	DLLICLIENT prosper::Shader *get_shader(const std::string &shaderName);
	DLLICLIENT bool is_game_active();
	DLLICLIENT std::shared_ptr<::Model> create_model(bool bAddReference=true);
	DLLICLIENT bool is_game_initialized();
	DLLICLIENT void load_as_gui_module();
	DLLICLIENT void draw_frame(const std::function<void(const std::shared_ptr<prosper::IPrimaryCommandBuffer>&,uint32_t)> &fDrawFrame);
};

#endif