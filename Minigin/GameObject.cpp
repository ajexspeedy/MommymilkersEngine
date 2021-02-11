#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(){}

void dae::GameObject::Render() const
{
	m_RenderComponent.Render();
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_RenderComponent.SetTexture(filename);
	
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_RenderComponent.SetPosition(x,y);
	
}
