#include "pragma/iscene.h"
#include <pragma/c_engine.h>
#include <pragma/clientstate/clientstate.h>

extern DLLCLIENT CGame *c_game;

IScene::IScene(pragma::CSceneComponent &scene)
	: m_target(scene.GetHandle<pragma::CSceneComponent>())
{}

const pragma::CSceneComponent &IScene::GetTarget() const {return *m_target;}

IScene IScene::Create()
{
	pragma::CSceneComponent::CreateInfo createInfo {};
	auto scene = pragma::CSceneComponent::Create(createInfo);
	return IScene(*scene);
}
pragma::CSceneComponent &IScene::GetInternalScene() {return *static_cast<pragma::CSceneComponent*>(m_target.get());}
uint32_t IScene::GetWidth() const {return static_cast<pragma::CSceneComponent*>(m_target.get())->GetWidth();}
uint32_t IScene::GetHeight() const {return static_cast<pragma::CSceneComponent*>(m_target.get())->GetHeight();}
WorldEnvironment *IScene::GetWorldEnvironment() const {return static_cast<pragma::CSceneComponent*>(m_target.get())->GetWorldEnvironment();}
void IScene::SetWorldEnvironment(WorldEnvironment *env)
{
	if(env == nullptr)
		static_cast<pragma::CSceneComponent*>(m_target.get())->ClearWorldEnvironment();
	else
		static_cast<pragma::CSceneComponent*>(m_target.get())->SetWorldEnvironment(*env);
}
