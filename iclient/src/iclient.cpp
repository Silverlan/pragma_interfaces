#include "pragma/iclient.h"
#ifdef _WIN32
#include <Windows.h>
#endif
#include <mathutil/eulerangles.h>
#include <pragma/c_engine.h>
#include <pragma/clientstate/clientstate.h>
#include <image/prosper_render_target.hpp>
#include <prosper_render_pass.hpp>
#include <prosper_framebuffer.hpp>
#include <pragma/rendering/renderers/base_renderer.hpp>
#include <pragma/rendering/scene/util_draw_scene_info.hpp>
#include <pragma/entities/components/renderers/c_renderer_component.hpp>
#include "pragma/gui/wiluahandlewrapper.h"
#include "pragma/iscene.h"
#include <prosper_window.hpp>

extern DLLCLIENT CEngine *c_engine;
extern DLLCLIENT ClientState *client;
extern DLLCLIENT CGame *c_game;

static void add_client_callback(const std::string &identifier,const CallbackHandle &callback)
{
	client->AddCallback(identifier,callback);
}

static void add_game_callback(const std::string &identifier,const CallbackHandle &callback)
{
	if(c_game == nullptr)
		return;
	c_game->AddCallback(identifier,callback);
}

void iclient::draw_frame(const std::function<void()> &fDrawFrame)
{
	c_engine->GetRenderContext().DrawFrame([&fDrawFrame]() {
		fDrawFrame();
	});
}

const CallbackHandle &iclient::add_callback(Callback cb,const CallbackHandle &f)
{
	switch(cb)
	{
		case Callback::Think:
			client->AddThinkCallback(f);
			break;
		case Callback::Draw:
			add_client_callback("Draw",f);
			break;
		case Callback::DrawScene:
			add_game_callback("DrawScene",f);
			break;
		case Callback::OnLuaInitialized:
			add_game_callback("OnLuaInitialized",f);
			break;
		case Callback::OnGameStart:
			client->AddCallback("OnGameStart",f);
			break;
		case Callback::EndGame:
			client->AddCallback("EndGame",f);
			break;
		case Callback::OnGameInitialized:
			add_game_callback("OnGameInitialized",f);
			break;
		case Callback::PreRender:
			client->AddCallback("PreRender",f);
			break;
		case Callback::PostRender:
			client->AddCallback("PostRender",f);
			break;
		case Callback::EngineDraw:
			c_engine->AddCallback("Draw",f);
			break;
	};
	return f;
}

bool iclient::is_game_active() {return client->IsGameActive();}
bool iclient::is_game_initialized() {return is_game_active() && client->GetGameState()->IsGameInitialized();}
void iclient::load_as_gui_module() {client->InitializeGUIModule();}

std::shared_ptr<::Model> iclient::create_model(bool bAddReference)
{
	return c_game->CreateModel(bAddReference);
}

lua_State *iclient::get_lua_state() {return client->GetLuaState();}
lua_State *iclient::get_gui_lua_state() {return client->GetGUILuaState();}

void iclient::add_gui_lua_wrapper_factory(const std::function<luabind::object(lua_State*,WIBase&)> &f) {client->AddGUILuaWrapperFactory(f);}

double iclient::real_time() {return client->RealTime();}
double iclient::delta_time() {return client->DeltaTime();}
double iclient::last_think() {return client->LastThink();}

bool iclient::protected_lua_call(int nargs,int nresults)
{
	lua_State *m_lua = client->GetLuaState();
	int err = lua_pcall(m_lua,nargs,nresults,0);
	if(err == 0)
		return true;
	Lua::HandleLuaError(m_lua,static_cast<Lua::StatusCode>(err));
	return false;
}

GLFWwindow *iclient::get_context_window()
{
	auto &window = c_engine->GetWindow();
	return const_cast<GLFWwindow*>(window->GetGLFWWindow());
}

std::shared_ptr<prosper::Texture> iclient::get_presentation_texture()
{
	auto *scene = c_game->GetScene();
	auto *renderer = scene ? scene->GetRenderer() : nullptr;
	if(renderer == nullptr)
		return nullptr;
	return renderer->GetPresentationTexture()->shared_from_this();
}

const prosper::IPrContext &iclient::get_render_context() {return c_engine->GetRenderContext();}

IScene iclient::get_render_scene() {return IScene(*c_game->GetRenderScene());}
IScene iclient::get_main_scene() {return IScene(*c_game->GetScene());}

void iclient::draw_scene(const IScene &cam,const std::shared_ptr<prosper::IPrimaryCommandBuffer> &drawCmd,std::shared_ptr<prosper::RenderTarget> &rt)
{
	util::DrawSceneInfo drawSceneInfo {};
	drawSceneInfo.commandBuffer = drawCmd;
	drawSceneInfo.outputImage = rt->GetTexture().GetImage().shared_from_this();

	c_game->SetRenderClipPlane({});
	c_game->SetRenderScene(const_cast<pragma::CSceneComponent&>(cam.GetTarget()));
		c_game->RenderScene(drawSceneInfo);
	c_game->ResetRenderScene();
}

prosper::Shader *iclient::get_shader(const std::string &shaderName) {return c_engine->GetShader(shaderName).get();}
