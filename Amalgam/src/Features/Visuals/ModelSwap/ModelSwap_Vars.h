// ModelSwap Configuration Variables
// Add these to your Vars:: configuration system

namespace Vars::Visuals::ModelSwap
{
	// Enable/Disable the ModelSwap feature
	ConVar_t<bool> Enabled("ModelSwap_Enabled", false, "Enable local player model swapping");

	// Path to the replacement model file
	// Example: "models/player/scout/scout.mdl"
	ConVar_t<std::string> ReplacementModelPath("ModelSwap_ReplacementModel", "", "Path to replacement player model (e.g., models/player/scout/scout.mdl)");

	// Whether to also swap the viewmodel (hands/weapon)
	ConVar_t<bool> SwapViewmodel("ModelSwap_SwapViewmodel", false, "Also swap the viewmodel when swapping player model");
}
