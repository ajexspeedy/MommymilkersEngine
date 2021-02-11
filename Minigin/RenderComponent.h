#pragma once
#include "Transform.h"

namespace dae
{
	class Texture2D;
	class RenderComponent
	{

	public:
		void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
	private:

		Transform m_Transform;
		std::shared_ptr<Texture2D> m_Texture{};
	};
}