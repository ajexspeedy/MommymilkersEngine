#pragma once
#include "SceneObject.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include <map>

namespace dae
{
	enum class ComponentType
	{
		renderComponent, textComponent
	};

	class Texture2D;
	class GameObject final
	{
	public:
		GameObject(Component* component,const std::string& objectName);
		GameObject(const std::map<size_t,Component*>& components, const std::string& objectName);
		
		void Update();
		void Render()const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
		void SetObjectName(const std::string& name);

		bool AddComponent(Component& component);
		void UpdateComponents();
		std::string GetObjectName() const;
		
		

		GameObject() = default;
		virtual ~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::map<size_t, Component*> m_pComponents = {};
		std::string m_ObjectName{"Default"};
		RenderComponent* GetRenderComponent() const;
		TextComponent* GetTextComponent() const;
		float m_FPSCooldown = 0.f;
	};
}
