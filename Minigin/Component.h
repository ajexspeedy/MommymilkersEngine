#pragma once

namespace dae
{
	class Component
	{
	public:
		

		virtual int GetComponentId() const = 0;
		virtual void Update() = 0;

		Component() = default;
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
	};
}
