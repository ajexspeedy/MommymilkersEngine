#include "MiniginPCH.h"
#include "GameObject.h"
#include "Renderer.h"
#include "TimeManager.h"




dae::GameObject::GameObject(Component* component, const std::string& objectName)
{
	AddComponent(*component);
	SetObjectName(objectName);
}

dae::GameObject::GameObject(const std::map<size_t, Component*>& components, const std::string& objectName)
{
	for (std::pair<size_t, Component*> component : components)
	{
		AddComponent(*component.second);
	}
	SetObjectName(objectName);
}

void dae::GameObject::Update()
{
	if (m_ObjectName == "FPS_Counter" && m_FPSCooldown <= 0.f)
	{
		GetTextComponent()->SetText("FPS: " + std::to_string(int(TimeManager::GetInstance().GetFPS())));
		m_FPSCooldown = 1.f;
	}
	m_FPSCooldown -= TimeManager::GetInstance().GetDeltaTime();
	UpdateComponents();
}

void dae::GameObject::Render() const
{

	if(m_pComponents.find(size_t(ComponentType::renderComponent)) != m_pComponents.end())
		GetRenderComponent()->Render();
	if(m_pComponents.find(size_t(ComponentType::textComponent)) != m_pComponents.end())
		GetTextComponent()->Render();

}

void dae::GameObject::SetTexture(const std::string& filename)
{
	if (m_pComponents.find(size_t(ComponentType::renderComponent)) != m_pComponents.end())
		GetRenderComponent()->SetTexture(filename);

}

void dae::GameObject::SetPosition(float x, float y)
{
	if (m_pComponents.find(size_t(ComponentType::renderComponent)) != m_pComponents.end())
		GetRenderComponent()->SetPosition(x, y);
	if (m_pComponents.find(size_t(ComponentType::textComponent)) != m_pComponents.end())
		GetTextComponent()->SetPosition(x, y);
}

void dae::GameObject::SetObjectName(const std::string& name)
{
	m_ObjectName = name;
}

bool dae::GameObject::AddComponent(Component& component)
{
	for (size_t index{ 0 }; index < m_pComponents.size(); index++)
	{
		if (m_pComponents.count(component.GetComponentId()) > 0)
		{
			// Component already exists
			return false;
		}

	}
	m_pComponents[component.GetComponentId()] = &component;
	return true;
}

void dae::GameObject::UpdateComponents()
{
	for (auto& component : m_pComponents)
	{
		component.second->Update();
	}
}

std::string dae::GameObject::GetObjectName() const
{
	return m_ObjectName;
}


dae::RenderComponent* dae::GameObject::GetRenderComponent() const
{

	return dynamic_cast<RenderComponent*>(m_pComponents.at(size_t(ComponentType::renderComponent)));
}

dae::TextComponent* dae::GameObject::GetTextComponent() const
{
	return  dynamic_cast<TextComponent*>(m_pComponents.at(size_t(ComponentType::textComponent)));
}
