#pragma once
#include "lmpch.h"
#include "EditorWindow.h"
#include <imgui/imgui.h>

namespace Lumos
{
	class Entity;

	class HierarchyWindow : public EditorWindow
	{
	public:
		HierarchyWindow();
		~HierarchyWindow() = default;

		void DrawNode(Entity* node, bool defaultOpen = false);
		void OnImGui() override;

	private:
		ImGuiTextFilter m_HierarchyFilter;
		Entity* m_DoubleClicked = nullptr;
		Entity* m_HadRecentDroppedEntity = nullptr;
		Entity* m_CopiedEntity = nullptr;
	};
}