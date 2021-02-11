#pragma once
#include "Component.h"
#include "Transform.h"


namespace dae
{
	class Texture2D;
	class RenderComponent: public Component
	{

	public:

		int GetComponentId() const override;
		void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
	private:

		Transform m_Transform;
		std::shared_ptr<Texture2D> m_Texture{};
	};
}