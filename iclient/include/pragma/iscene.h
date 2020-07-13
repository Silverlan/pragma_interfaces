#ifndef __ISCENE_H__
#define __ISCENE_H__

#include "iclientmodule.h"
#include "ivector.h"
#include "imatrix.h"
#include <memory>
#include <vector>

class WorldEnvironment;
class Scene;
class DLLICLIENT IScene
{
private:
	std::shared_ptr<void> m_target;
public:
	IScene(const std::shared_ptr<void>&);
	const std::shared_ptr<void> &GetTarget() const;
	static IScene Create();
	Scene &GetInternalScene();
	
	uint32_t GetWidth() const;
	uint32_t GetHeight() const;

	WorldEnvironment *GetWorldEnvironment() const;
	void SetWorldEnvironment(WorldEnvironment *env);
};

#endif
