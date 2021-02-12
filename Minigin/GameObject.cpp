#include "MiniginPCH.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

dae::GameObject::GameObject(Component & component)
{
	AddComponent(component);
}

dae::GameObject::GameObject(const std::map<size_t, Component*>&components) :
	GameObject()
{
	for (std::pair<size_t, Component*> component : components)
	{
		m_pComponents[component.first] = component.second;
	}
}

void dae::GameObject::Update() {}

void dae::GameObject::Render() const
{
	if (m_pComponents.size() > 0)
	{
		/*ComponentType componentType = ComponentType::renderComponent;
		const size_t keyValue = size_t(componentType);
		auto renderComponent = dynamic_cast<RenderComponent*>(m_pComponents.find(keyValue)->second);
		*/

	}
	m_RenderComponent.Render();
}

void dae::GameObject::SetTexture(const std::string & filename)
{
	// TODO call rendercomponent functions via component*
	if (m_pComponents.size() > 0)
	{
		ComponentType componentType = ComponentType::renderComponent;
		auto* renderComponent = dynamic_cast<RenderComponent*>(m_pComponents[int(componentType)]);
		renderComponent->SetTexture(filename);

	}
	m_RenderComponent.SetTexture(filename);

}

void dae::GameObject::SetPosition(float x, float y)
{
	m_RenderComponent.SetPosition(x, y);

}

bool dae::GameObject::AddComponent(Component & component)
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


