#pragma once
#include "RenderComponent.h"

namespace dae
{
	class Font;

	class TextComponent : public RenderComponent
	{
	public:
		explicit TextComponent(const std::string& text, const std::shared_ptr<Font>& font);
		int GetComponentId() const override;

		void Update() override;
		void SetText(const std::string& text);
	
	protected:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
	};
}
