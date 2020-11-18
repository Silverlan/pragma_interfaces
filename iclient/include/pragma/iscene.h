#ifndef __ISCENE_H__
#define __ISCENE_H__

#include "iclientmodule.h"
#include "ivector.h"
#include "imatrix.h"
#include <sharedutils/util_weak_handle.hpp>
#include <memory>
#include <vector>

class WorldEnvironment;
class Scene;
namespace pragma {class CSceneComponent;};
class DLLICLIENT IScene
{
public:
	IScene(pragma::CSceneComponent &scene);
	const pragma::CSceneComponent &GetTarget() const;
	static IScene Create();
	pragma::CSceneComponent &GetInternalScene();
	
	uint32_t GetWidth() const;
	uint32_t GetHeight() const;

	WorldEnvironment *GetWorldEnvironment() const;
	void SetWorldEnvironment(WorldEnvironment *env);
private:
	util::WeakHandle<pragma::CSceneComponent> m_target {};
};

#endif
