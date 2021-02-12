#pragma once
#include "SceneObject.h"
#include "RenderComponent.h"
#include <map>

namespace dae
{
	enum class ComponentType
	{
		renderComponent
	};
	class Texture2D;
	class GameObject
	{
	public:
		GameObject(Component& component);
		GameObject(const std::map<size_t,Component*>& components);
		
		void Update();
		void Render()const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		bool AddComponent(Component& component);
		

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::map<size_t, Component*> m_pComponents = {};
		RenderComponent m_RenderComponent;
		Transform m_Transform;
		std::shared_ptr<Texture2D> m_Texture{};
	};
}
