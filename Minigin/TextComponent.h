#pragma once
#include "RenderComponent.h"

namespace dae
{
	class Font;

	class TextComponent : public RenderComponent
	{
	public:
		explicit TextComponent(const std::string& text, const std::shared_ptr<Font>& font);
		virtual ~TextComponent() = default;
		int GetComponentId() const override;

		virtual void Update() override;
		void SetText(const std::string& text);

		
	protected:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		void UpdateTexture();
	};
}
