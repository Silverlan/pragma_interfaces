#include "pragma/iscene.h"
#include <pragma/c_engine.h>
#include <pragma/clientstate/clientstate.h>

extern DLLCLIENT CGame *c_game;

IScene::IScene(const std::shared_ptr<void> &scene)
	: m_target(scene)
{}

const std::shared_ptr<void> &IScene::GetTarget() const {return m_target;}

IScene IScene::Create()
{
	Scene::CreateInfo createInfo {};
	auto scene = Scene::Create(createInfo);
	return IScene(scene);
}
Scene &IScene::GetInternalScene() {return *static_cast<Scene*>(m_target.get());}
uint32_t IScene::GetWidth() const {return static_cast<Scene*>(m_target.get())->GetWidth();}
uint32_t IScene::GetHeight() const {return static_cast<Scene*>(m_target.get())->GetHeight();}
WorldEnvironment *IScene::GetWorldEnvironment() const {return static_cast<Scene*>(m_target.get())->GetWorldEnvironment();}
void IScene::SetWorldEnvironment(WorldEnvironment *env)
{
	if(env == nullptr)
		static_cast<Scene*>(m_target.get())->ClearWorldEnvironment();
	else
		static_cast<Scene*>(m_target.get())->SetWorldEnvironment(*env);
}
