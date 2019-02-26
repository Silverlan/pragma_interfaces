#include "pragma/iclient.h"
#ifdef _WIN32
#include <Windows.h>
#endif
#include <btBulletCollisionCommon.h>
#include <mathutil/eulerangles.h>
#include <pragma/c_engine.h>
#include <pragma/clientstate/clientstate.h>
#include <image/prosper_render_target.hpp>
#include <prosper_render_pass.hpp>
#include <prosper_framebuffer.hpp>
#include "pragma/gui/wiluahandlewrapper.h"
#include "pragma/iscene.h"

#pragma comment(lib,"Anvil.lib")
#pragma comment(lib,"glfw.lib")
#pragma comment(lib,"cengine.lib")
#pragma comment(lib,"shared.lib")
#pragma comment(lib,"client.lib")
#pragma comment(lib,"engine.lib")
#pragma comment(lib,"cengine.lib")
#pragma comment(lib,"lua51.lib")
#pragma comment(lib,"luasystem.lib")
#pragma comment(lib,"luabind.lib")
#pragma comment(lib,"sharedutils.lib")
#pragma comment(lib,"mathutil.lib")
#pragma comment(lib,"prosper.lib")

extern DLLCENGINE CEngine *c_engine;
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

void iclient::draw_frame(const std::function<void(const std::shared_ptr<prosper::PrimaryCommandBuffer>&,uint32_t)> &fDrawFrame)
{
	c_engine->DrawFrame([&fDrawFrame](const std::shared_ptr<prosper::PrimaryCommandBuffer> &drawCmd,uint32_t nSwapchainImage) {
		fDrawFrame(drawCmd,nSwapchainImage);
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

void iclient::add_gui_lua_wrapper_factory(const std::function<luabind::object(lua_State*,WIBase*)> &f) {client->AddGUILuaWrapperFactory(f);}

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
}

GLFWwindow *iclient::get_context_window()
{
	auto &window = c_engine->GetWindow();
	return const_cast<GLFWwindow*>(window.GetGLFWWindow());
}

const std::shared_ptr<prosper::RenderTarget> &iclient::get_screen_render_target()
{
	auto &scene = c_game->GetScene();
	return scene->GetHDRInfo().hdrRenderTarget;
}

const prosper::Context &iclient::get_render_context() {return *c_engine;}

IScene iclient::get_render_scene() {return IScene(c_game->GetRenderScene());}
IScene iclient::get_main_scene() {return IScene(c_game->GetScene());}

void iclient::draw_scene(const IScene &cam,const std::shared_ptr<prosper::PrimaryCommandBuffer> &drawCmd,std::shared_ptr<prosper::RenderTarget> &rt)
{
	c_game->SetRenderClipPlane({});
	c_game->SetRenderScene(std::static_pointer_cast<Scene>(cam.GetTarget()));
		c_game->RenderScene(const_cast<std::shared_ptr<prosper::PrimaryCommandBuffer>&>(drawCmd),rt);
	c_game->SetRenderScene(nullptr);
}

prosper::Shader *iclient::get_shader(const std::string &shaderName) {return c_engine->GetShader(shaderName).get();}
