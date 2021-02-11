#include "MiniginPCH.h"
#include "RenderComponent.h"

#include "Renderer.h"
#include "ResourceManager.h"
using namespace dae;
void RenderComponent::Render() const
{

	const auto pos = m_Transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void RenderComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void RenderComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
