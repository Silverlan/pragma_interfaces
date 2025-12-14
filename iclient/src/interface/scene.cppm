// SPDX-FileCopyrightText: (c) 2019 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

module;

#include "definitions.hpp"

export module pragma.iclient:scene;

import pragma.client;

export class DLLICLIENT IScene {
  public:
	IScene(pragma::CSceneComponent &scene);
	const pragma::CSceneComponent &GetTarget() const;
	static IScene Create();
	pragma::CSceneComponent &GetInternalScene();

	uint32_t GetWidth() const;
	uint32_t GetHeight() const;

	pragma::rendering::WorldEnvironment *GetWorldEnvironment() const;
	void SetWorldEnvironment(pragma::rendering::WorldEnvironment *env);
  private:
	pragma::util::TWeakSharedHandle<pragma::CSceneComponent> m_target {};
};
