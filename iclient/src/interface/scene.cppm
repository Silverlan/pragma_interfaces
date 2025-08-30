// SPDX-FileCopyrightText: (c) 2019 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

module;

#include "iclient_definitions.hpp"
#include <sharedutils/util_shared_handle.hpp>
#include <pragma/c_engine.h>
#include <pragma/clientstate/clientstate.h>

export module pragma.iclient:scene;

export class DLLICLIENT IScene {
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
	util::TWeakSharedHandle<pragma::CSceneComponent> m_target {};
};
