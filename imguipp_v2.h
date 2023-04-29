#pragma once
#include "imgui.h"
#include "imgui_internal.h"

#include <string>
#include <vector>
#include <functional>

#define MAX_RGB 255.0
#define HELPMARKER(str) ImGui::SameLine(); ImGui::TextColored(ImColor(220, 190, 0, 255), "(?)"); if (ImGui::IsItemHovered()) ImGui::SetTooltip(str)
#pragma warning(disable: 26812 26815)

namespace ImGuiPP
{
	void Line(int newId)
	{
		std::string id = ("imguipp_line_" + std::to_string(newId));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
		{
			ImGui::BeginChild(id.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 1), false);
			ImGui::Separator();
			ImGui::EndChild();
		}
		ImGui::PopStyleColor();
	}

	void Linevertical()
	{
		ImGui::SameLine();
		ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
		ImGui::SameLine();
	}

	void CenterText(const char* text, int lineId, bool separator)
	{
		if (text == nullptr)
			return;

		ImGui::Spacing();
		ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (ImGui::CalcTextSize(text).x / 2));
		ImGui::Text(text);
		ImGui::Spacing();

		if (true == separator)
			Line(lineId);
	}

	void CenterTextEx(const char* text, float width, int lineId, bool separator)
	{
		if (text == nullptr)
			return;

		ImGui::Spacing();
		ImGui::SameLine((width / 2) - (ImGui::CalcTextSize(text).x / 2));
		ImGui::Text(text);
		ImGui::Spacing();

		if (true == separator)
			Line(lineId);
	}

	void DrawTextImGui(ImVec2 position, ImColor color, const char* format, ...)
	{
		if (format == nullptr)
			return;

		char buffer[512];

		va_list  args;
		va_start(args, format);
		vsnprintf_s(buffer, sizeof(buffer), format, args);
		va_end(args);

		ImGui::GetBackgroundDrawList()->AddText(position, color, format, buffer);
	}

	void DrawCircle(ImVec2 windowSize, ImColor color, float radius, float thickness = 1)
	{
		ImGui::GetBackgroundDrawList()->AddCircle(windowSize, radius, color, 100, thickness);
	}

	float GetX()
	{
		return ImGui::GetContentRegionAvail().x;
	}

	float GetY()
	{
		return ImGui::GetContentRegionAvail().y;
	}

	ImVec4 ToVec4(float r, float g, float b, float a)
	{
		return ImVec4(r / MAX_RGB, g / MAX_RGB, b / MAX_RGB, a / MAX_RGB);
	}
}