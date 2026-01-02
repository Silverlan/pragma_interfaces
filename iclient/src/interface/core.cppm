// SPDX-FileCopyrightText: (c) 2019 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

export module pragma.iclient:core;

import :scene;

import pragma.client;

export namespace iclient {
	enum class Callback : uint32_t { Think = 0, Draw, DrawScene, OnLuaInitialized, OnGameStart, EndGame, OnGameInitialized, PreRender, PostRender, EngineDraw };
	DLLICLIENT const CallbackHandle &add_callback(Callback cb, const CallbackHandle &f);
	DLLICLIENT lua::State *get_lua_state();
	DLLICLIENT lua::State *get_gui_lua_state();
	DLLICLIENT void add_gui_lua_wrapper_factory(const std::function<luabind::adl::object(lua::State *, pragma::gui::types::WIBase &)> &f);
	DLLICLIENT double real_time();
	DLLICLIENT double delta_time();
	DLLICLIENT double last_think();
	DLLICLIENT bool protected_lua_call(int nargs = 0, int nresults = 0);
	// DLLICLIENT GLFWwindow *get_context_window();
	DLLICLIENT std::shared_ptr<prosper::Texture> get_presentation_texture();
	DLLICLIENT IScene get_render_scene();
	DLLICLIENT IScene get_main_scene();
	DLLICLIENT const prosper::IPrContext &get_render_context();
	DLLICLIENT void draw_scene(const IScene &cam, const std::shared_ptr<prosper::IPrimaryCommandBuffer> &drawCmd, std::shared_ptr<prosper::RenderTarget> &rt);
	DLLICLIENT prosper::Shader *get_shader(const std::string &shaderName);
	DLLICLIENT bool is_game_active();
	DLLICLIENT std::shared_ptr<pragma::asset::Model> create_model(bool bAddReference = true);
	DLLICLIENT bool is_game_initialized();
	DLLICLIENT void load_as_gui_module();
	DLLICLIENT void draw_frame(const std::function<void()> &fDrawFrame);
};
