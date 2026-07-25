#include "ModelSwapMenu.h"
#include "ModelSwap.h"
#include "ModelSwap_Vars.h"

char CModelSwapMenu::szModelPath[256] = {};

void CModelSwapMenu::Draw()
{
	if (ImGui::CollapsingHeader("Model Swap##ModelSwap", ImGuiTreeNodeFlags_DefaultOpen))
	{
		// Enable/Disable checkbox
		bool bEnabled = Vars::Visuals::ModelSwap::Enabled.Value;
		if (ImGui::Checkbox("Enable Model Swap##ModelSwap_Enabled", &bEnabled))
		{
			Vars::Visuals::ModelSwap::Enabled.Value = bEnabled;
		}
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Swap your model to another player model (client-side only)\nOther players always see your real model");

		impl::Spacing(2);

		// Model path input
		strcpy_s(szModelPath, sizeof(szModelPath), Vars::Visuals::ModelSwap::ReplacementModelPath.Value.c_str());
		ImGui::PushItemWidth(300);
		if (ImGui::InputText("Model Path##ModelSwap_Path", szModelPath, sizeof(szModelPath), ImGuiInputTextFlags_EnterReturnsTrue))
		{
			Vars::Visuals::ModelSwap::ReplacementModelPath.Value = szModelPath;
		}
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Example: models/player/scout/scout.mdl\nUse same-class models to avoid animation glitches");
		ImGui::PopItemWidth();

		impl::Spacing(1);

		// Viewmodel swap checkbox
		bool bSwapViewmodel = Vars::Visuals::ModelSwap::SwapViewmodel.Value;
		if (ImGui::Checkbox("Swap Viewmodel##ModelSwap_Viewmodel", &bSwapViewmodel))
		{
			Vars::Visuals::ModelSwap::SwapViewmodel.Value = bSwapViewmodel;
		}
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Also swap first-person hands and weapon model");

		impl::Spacing(2);

		// Common model presets
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Common Models:");
		
		const char* aModels[] = {
			"models/player/scout/scout.mdl",
			"models/player/soldier/soldier.mdl",
			"models/player/pyro/pyro.mdl",
			"models/player/demoman/demoman.mdl",
			"models/player/heavy/heavy.mdl",
			"models/player/engineer/engineer.mdl",
			"models/player/medic/medic.mdl",
			"models/player/sniper/sniper.mdl",
			"models/player/spy/spy.mdl"
		};
		const char* aNames[] = {
			"Scout",
			"Soldier",
			"Pyro",
			"Demoman",
			"Heavy",
			"Engineer",
			"Medic",
			"Sniper",
			"Spy"
		};

		int iCols = 3;
		for (int i = 0; i < IM_ARRAYSIZE(aModels); i++)
		{
			if (ImGui::Button(aNames[i], ImVec2(90, 25)))
			{
				Vars::Visuals::ModelSwap::ReplacementModelPath.Value = aModels[i];
				strcpy_s(szModelPath, sizeof(szModelPath), aModels[i]);
			}

			if ((i + 1) % iCols != 0 && i != IM_ARRAYSIZE(aModels) - 1)
				ImGui::SameLine();
		}

		impl::Spacing(2);

		// Anti-cheat warning
		ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.0f, 1.0f), "\u26a0 Anti-Cheat Warning:");
		ImGui::TextWrapped(
			"This feature is client-side only. Other players always see your real model. "
			"Use on private/listen servers only. Incompatible models may cause animation glitches. "
			"Disable before joining public servers."
		);
	}
}
