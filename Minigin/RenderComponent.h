﻿#pragma once
#include "Component.h"
#include "Transform.h"


namespace dae
{
	class Texture2D;
	class RenderComponent: public Component
	{

	public:
		RenderComponent() = default;
		RenderComponent(const std::string& filename, const float x = 0.f,const float y = 0.f);
		int GetComponentId() const override;
		void Render() const;
		virtual void Update();
		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
	protected:

		Transform m_Transform;
		std::shared_ptr<Texture2D> m_Texture{};
	};
}