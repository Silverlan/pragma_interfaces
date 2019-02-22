#ifndef __ISCENE_H__
#define __ISCENE_H__

#include "iclientmodule.h"
#include "ivector.h"
#include "imatrix.h"
#include <memory>
#include <vector>

class WorldEnvironment;
class DLLICLIENT IScene
{
private:
	std::shared_ptr<void> m_target;
public:
	IScene(const std::shared_ptr<void>&);
	const std::shared_ptr<void> &GetTarget() const;
	static IScene Create(uint32_t width,uint32_t height,float fov,float fovView,float aspectRatio,float nearZ,float farZ);
	
	uint32_t GetWidth() const;
	uint32_t GetHeight() const;

	void UpdateMatrices();
	void UpdateViewMatrix();
	void UpdateProjectionMatrix();
	void UpdateViewProjectionMatrix();
	void UpdateProjectionMatrices();
	void SetFOV(float fov);
	void SetViewFOV(float fov);
	void SetAspectRatio(float aspectRatio);
	void SetZNear(float nearZ);
	void SetZFar(float farZ);
	void SetUp(const IVector3 &up);
	void SetForward(const IVector3 &forward);
	void SetPos(const IVector3 &pos);
	void SetViewMatrix(const IMat4 &mat);
	void SetViewProjectionMatrix(const IMat4 &mat);
	void SetProjectionMatrix(const IMat4 &mat);

	float GetFOV() const;
	float GetFOVRad() const;
	float GetViewFOV() const;
	float GetViewFOVRad() const;
	float GetAspectRatio() const;
	float GetZNear() const;
	float GetZFar() const;
	const IVector3 &GetUp() const;
	const IVector3 &GetPos() const;
	const IVector3 &GetForward() const;
	const IMat4 &GetViewMatrix() const;
	const IMat4 &GetViewProjectionMatrix() const;
	const IMat4 &GetProjectionMatrix() const;
	WorldEnvironment *GetWorldEnvironment() const;
	void SetWorldEnvironment(WorldEnvironment *env);
	const std::shared_ptr<void> &GetLightSourceListInfo() const;
	void SetLightSourceListInfo(const std::shared_ptr<void> &lightSources);
	void InitializeRenderTarget();
	void LinkEntities(IScene &other);
};

#endif
