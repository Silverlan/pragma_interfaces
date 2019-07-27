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
	static IScene Create(uint32_t width,uint32_t height);
	
	uint32_t GetWidth() const;
	uint32_t GetHeight() const;

	WorldEnvironment *GetWorldEnvironment() const;
	void SetWorldEnvironment(WorldEnvironment *env);
	const std::shared_ptr<void> &GetLightSourceListInfo() const;
	void SetLightSourceListInfo(const std::shared_ptr<void> &lightSources);
	void InitializeRenderTarget();
	void LinkEntities(IScene &other);
};

#endif
