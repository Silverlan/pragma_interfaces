#include "pragma/iscene.h"
#include <pragma/c_engine.h>
#include <pragma/clientstate/clientstate.h>

extern DLLCLIENT CGame *c_game;

IScene::IScene(const std::shared_ptr<void> &scene)
	: m_target(scene)
{}

const std::shared_ptr<void> &IScene::GetTarget() const {return m_target;}

IScene IScene::Create(uint32_t width,uint32_t height,float fov,float fovView,float aspectRatio,float nearZ,float farZ)
{
	Scene::CreateInfo createInfo {width,height,fov,fovView,nearZ,farZ};
	auto scene = Scene::Create(createInfo);
	return IScene(scene);
}

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
const std::shared_ptr<void> &IScene::GetLightSourceListInfo() const {return static_cast<Scene*>(m_target.get())->GetLightSourceListInfo();}
void IScene::SetLightSourceListInfo(const std::shared_ptr<void> &lightSources)
{
	static_cast<Scene*>(m_target.get())->SetLights(std::static_pointer_cast<Scene::LightListInfo>(lightSources));
}
void IScene::LinkEntities(IScene &other)
{
	static_cast<Scene*>(m_target.get())->LinkEntities(*static_cast<Scene*>(other.m_target.get()));
}
void IScene::InitializeRenderTarget() {static_cast<Scene*>(m_target.get())->InitializeRenderTarget();}

void IScene::UpdateMatrices() {return static_cast<Scene*>(m_target.get())->camera->UpdateMatrices();}
void IScene::UpdateViewMatrix() {return static_cast<Scene*>(m_target.get())->camera->UpdateViewMatrix();}
void IScene::UpdateProjectionMatrix() {return static_cast<Scene*>(m_target.get())->camera->UpdateProjectionMatrix();}
void IScene::UpdateViewProjectionMatrix() {return static_cast<Scene*>(m_target.get())->camera->UpdateViewProjectionMatrix();}
void IScene::UpdateProjectionMatrices() {return static_cast<Scene*>(m_target.get())->camera->UpdateProjectionMatrices();}
void IScene::SetFOV(float fov) {static_cast<Scene*>(m_target.get())->camera->SetFOV(fov);}
void IScene::SetViewFOV(float fov) {static_cast<Scene*>(m_target.get())->camera->SetViewFOV(fov);}
void IScene::SetAspectRatio(float aspectRatio) {static_cast<Scene*>(m_target.get())->camera->SetAspectRatio(aspectRatio);}
void IScene::SetZNear(float nearZ) {static_cast<Scene*>(m_target.get())->camera->SetZNear(nearZ);}
void IScene::SetZFar(float farZ) {static_cast<Scene*>(m_target.get())->camera->SetZFar(farZ);}
void IScene::SetUp(const IVector3 &up) {static_cast<Scene*>(m_target.get())->camera->SetUp(reinterpret_cast<const Vector3&>(up));}
void IScene::SetForward(const IVector3 &forward) {static_cast<Scene*>(m_target.get())->camera->SetForward(reinterpret_cast<const Vector3&>(forward));}
void IScene::SetPos(const IVector3 &pos) {static_cast<Scene*>(m_target.get())->camera->SetPos(reinterpret_cast<const Vector3&>(pos));}
void IScene::SetViewMatrix(const IMat4 &mat) {static_cast<Scene*>(m_target.get())->camera->SetViewMatrix(reinterpret_cast<const Mat4&>(mat));}
void IScene::SetViewProjectionMatrix(const IMat4 &mat) {static_cast<Scene*>(m_target.get())->camera->SetViewProjectionMatrix(reinterpret_cast<const Mat4&>(mat));}
void IScene::SetProjectionMatrix(const IMat4 &mat) {static_cast<Scene*>(m_target.get())->camera->SetProjectionMatrix(reinterpret_cast<const Mat4&>(mat));}

float IScene::GetFOV() const {return static_cast<Scene*>(m_target.get())->camera->GetFOV();}
float IScene::GetFOVRad() const {return static_cast<Scene*>(m_target.get())->camera->GetFOVRad();}
float IScene::GetViewFOV() const {return static_cast<Scene*>(m_target.get())->camera->GetViewFOV();}
float IScene::GetViewFOVRad() const {return static_cast<Scene*>(m_target.get())->camera->GetViewFOVRad();}
float IScene::GetAspectRatio() const {return static_cast<Scene*>(m_target.get())->camera->GetAspectRatio();}
float IScene::GetZNear() const {return static_cast<Scene*>(m_target.get())->camera->GetZNear();}
float IScene::GetZFar() const {return static_cast<Scene*>(m_target.get())->camera->GetZFar();}
const IVector3 &IScene::GetUp() const {return reinterpret_cast<const IVector3&>(static_cast<Scene*>(m_target.get())->camera->GetUp());}
const IVector3 &IScene::GetPos() const {return reinterpret_cast<const IVector3&>(static_cast<Scene*>(m_target.get())->camera->GetPos());}
const IVector3 &IScene::GetForward() const {return reinterpret_cast<const IVector3&>(static_cast<Scene*>(m_target.get())->camera->GetForward());}
const IMat4 &IScene::GetViewMatrix() const {return reinterpret_cast<const IMat4&>(static_cast<Scene*>(m_target.get())->camera->GetViewMatrix());}
const IMat4 &IScene::GetViewProjectionMatrix() const {return reinterpret_cast<const IMat4&>(static_cast<Scene*>(m_target.get())->camera->GetViewProjectionMatrix());}
const IMat4 &IScene::GetProjectionMatrix() const {return reinterpret_cast<const IMat4&>(static_cast<Scene*>(m_target.get())->camera->GetProjectionMatrix());}
