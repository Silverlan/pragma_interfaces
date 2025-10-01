// SPDX-FileCopyrightText: (c) 2019 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

module;

#ifdef _WIN32
#include <Windows.h>
#endif
#include <mathutil/eulerangles.h>
#include <image/prosper_render_target.hpp>
#include <prosper_render_pass.hpp>
#include <prosper_framebuffer.hpp>
#include <prosper_window.hpp>

module pragma.iclient;

import :core;

import pragma.client;
// import pragma.scripting.lua;

template<typename TCPPM>
TCPPM *CGame::GetScene() { return static_cast<pragma::CSceneComponent*>(m_scene.get()); }
template<typename TCPPM>
TCPPM *CGame::GetRenderScene() { return static_cast<pragma::CSceneComponent*>(m_renderScene.get()); }
template<typename TCPPM>
void CGame::SetRenderScene(TCPPM &scene) { m_renderScene = scene.GetHandle(); }

static ClientState *cl() {return dynamic_cast<ClientState*>(pragma::get_client_state());}
static CGame *cg() {return cl()->GetGameState();}

static void add_client_callback(const std::string &identifier, const CallbackHandle &callback) { pragma::get_client_state()->AddCallback(identifier, callback); }

static void add_game_callback(const std::string &identifier, const CallbackHandle &callback)
{
	if(pragma::get_cgame() == nullptr)
		return;
	pragma::get_cgame()->AddCallback(identifier, callback);
}

void iclient::draw_frame(const std::function<void()> &fDrawFrame)
{
	pragma::get_cengine()->GetRenderContext().DrawFrame([&fDrawFrame]() { fDrawFrame(); });
}

const CallbackHandle &iclient::add_callback(Callback cb, const CallbackHandle &f)
{
	auto *client = pragma::get_client_state();
	switch(cb) {
	case Callback::Think:
		client->AddThinkCallback(f);
		break;
	case Callback::Draw:
		add_client_callback("Draw", f);
		break;
	case Callback::DrawScene:
		add_game_callback("DrawScene", f);
		break;
	case Callback::OnLuaInitialized:
		add_game_callback("OnLuaInitialized", f);
		break;
	case Callback::OnGameStart:
		client->AddCallback("OnGameStart", f);
		break;
	case Callback::EndGame:
		client->AddCallback("EndGame", f);
		break;
	case Callback::OnGameInitialized:
		add_game_callback("OnGameInitialized", f);
		break;
	case Callback::PreRender:
		client->AddCallback("PreRender", f);
		break;
	case Callback::PostRender:
		client->AddCallback("PostRender", f);
		break;
		case Callback::EngineDraw:
		pragma::get_cengine()->AddCallback("Draw", f);
		break;
	};
	return f;
}

bool iclient::is_game_active() { return pragma::get_client_state()->IsGameActive(); }
bool iclient::is_game_initialized() { return is_game_active() && pragma::get_client_state()->GetGameState()->IsGameInitialized(); }
void iclient::load_as_gui_module() { pragma::get_client_state()->InitializeGUIModule(); }

std::shared_ptr<::Model> iclient::create_model(bool bAddReference) { return pragma::get_cgame()->CreateModel(bAddReference); }

lua_State *iclient::get_lua_state() { return pragma::get_client_state()->GetLuaState(); }
lua_State *iclient::get_gui_lua_state() { return pragma::get_client_state()->GetGUILuaState(); }

void iclient::add_gui_lua_wrapper_factory(const std::function<luabind::object(lua_State *, WIBase &)> &f) { pragma::get_client_state()->AddGUILuaWrapperFactory(f); }

double iclient::real_time() { return pragma::get_client_state()->RealTime(); }
double iclient::delta_time() { return pragma::get_client_state()->DeltaTime(); }
double iclient::last_think() { return pragma::get_client_state()->LastThink(); }

bool iclient::protected_lua_call(int nargs, int nresults)
{
	lua_State *l = pragma::get_client_state()->GetLuaState();
	return pragma::scripting::lua::protected_call(l, nargs, nresults) == Lua::StatusCode::Ok;
}

GLFWwindow *iclient::get_context_window()
{
	auto &window = pragma::get_cengine()->GetWindow();
	return const_cast<GLFWwindow *>(window->GetGLFWWindow());
}

template<typename TCPPM>
	TCPPM *pragma::CSceneComponent::GetRenderer() { return static_cast<TCPPM*>(m_renderer.get()); }
std::shared_ptr<prosper::Texture> iclient::get_presentation_texture()
{
	auto *scene = pragma::get_cgame()->GetScene<pragma::CSceneComponent>();
	auto *renderer = scene ? scene->GetRenderer<pragma::CRendererComponent>() : nullptr;
	if(renderer == nullptr)
		return nullptr;
	return renderer->GetPresentationTexture()->shared_from_this();
}

const prosper::IPrContext &iclient::get_render_context() { return pragma::get_cengine()->GetRenderContext(); }

IScene iclient::get_render_scene() { return IScene(*pragma::get_cgame()->GetRenderScene<pragma::CSceneComponent>()); }
IScene iclient::get_main_scene() { return IScene(*pragma::get_cgame()->GetScene<pragma::CSceneComponent>()); }

void iclient::draw_scene(const IScene &cam, const std::shared_ptr<prosper::IPrimaryCommandBuffer> &drawCmd, std::shared_ptr<prosper::RenderTarget> &rt)
{
	util::DrawSceneInfo drawSceneInfo {};
	drawSceneInfo.commandBuffer = drawCmd;
	drawSceneInfo.outputImage = rt->GetTexture().GetImage().shared_from_this();

	pragma::get_cgame()->SetRenderClipPlane({});
	pragma::get_cgame()->SetRenderScene(const_cast<pragma::CSceneComponent &>(cam.GetTarget()));
	pragma::get_cgame()->RenderScene(drawSceneInfo);
	pragma::get_cgame()->ResetRenderScene();
}

prosper::Shader *iclient::get_shader(const std::string &shaderName) { return pragma::get_cengine()->GetShader(shaderName).get(); }
