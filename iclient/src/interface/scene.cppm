// SPDX-FileCopyrightText: (c) 2019 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

module;

#include "definitions.hpp"
#include "pragma/entities/components/c_scene_component.hpp"
#include <sharedutils/util_shared_handle.hpp>
#include <pragma/c_engine.h>

export module pragma.iclient:scene;

import pragma.client.client_state;
import pragma.client.entities.components;

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
