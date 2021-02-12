#include "MiniginPCH.h"
#include "GameObject.h"
#include "Renderer.h"
#include "TimeManager.h"

dae::GameObject::~GameObject()
{
	for (std::pair<size_t, Component*> component : m_pComponents)
	{
		delete component.second;
		component.second = nullptr;
	}
}



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
	if (m_ObjectName == "FPS_Counter")
		GetTextComponent(ComponentType::textComponent)->SetText("FPS: " + std::to_string(TimeManager::GetInstance().GetFPS()));
	UpdateComponents();
}

void dae::GameObject::Render() const
{
	//TODO check if component is present
	GetRenderComponent(ComponentType::renderComponent)->Render();


}

void dae::GameObject::SetTexture(const std::string& filename)
{

	GetRenderComponent(ComponentType::renderComponent)->SetTexture(filename);

}

void dae::GameObject::SetPosition(float x, float y)
{
	GetRenderComponent(ComponentType::renderComponent)->SetPosition(x, y);

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


dae::RenderComponent* dae::GameObject::GetRenderComponent(ComponentType type) const
{

	return dynamic_cast<RenderComponent*>(m_pComponents.at(size_t(type)));
}

dae::TextComponent* dae::GameObject::GetTextComponent(ComponentType type) const
{
	return  dynamic_cast<TextComponent*>(m_pComponents.at(size_t(type)));
}
