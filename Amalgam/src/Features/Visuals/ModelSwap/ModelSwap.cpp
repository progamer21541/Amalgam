#include "ModelSwap.h"

void CModelSwap::Init()
{
	m_bInitialized = true;
	m_iModelIndex = -1;
	m_pCachedModel = nullptr;
	m_sLastModelPath = "";
}

void CModelSwap::Shutdown()
{
	ClearCache();
	m_bInitialized = false;
}

void CModelSwap::Reset()
{
	ClearCache();
}

void CModelSwap::ClearCache()
{
	m_iModelIndex = -1;
	m_pCachedModel = nullptr;
	m_sLastModelPath = "";
}

bool CModelSwap::IsValidModel(model_t* pModel) const
{
	if (!pModel)
		return false;

	// Basic validity check - model should have a valid name
	if (!pModel->name || pModel->name[0] == '\0')
		return false;

	return true;
}

model_t* CModelSwap::LoadAndCacheModel(const std::string& sModelPath)
{
	if (sModelPath.empty())
		return nullptr;

	// If path hasn't changed and we have a cached model, return it
	if (sModelPath == m_sLastModelPath && IsValidModel(m_pCachedModel))
		return m_pCachedModel;

	// Load the model index from the path
	int iModelIndex = I::ModelInfo->GetModelIndex(sModelPath.c_str());
	if (iModelIndex <= 0)
	{
		// Try to precache the model
		I::EngineClient->LoadModel(sModelPath.c_str());
		iModelIndex = I::ModelInfo->GetModelIndex(sModelPath.c_str());

		if (iModelIndex <= 0)
			return nullptr;
	}

	// Get the model_t pointer from index
	model_t* pModel = I::ModelInfo->GetModel(iModelIndex);
	if (!IsValidModel(pModel))
		return nullptr;

	// Cache it
	m_iModelIndex = iModelIndex;
	m_pCachedModel = pModel;
	m_sLastModelPath = sModelPath;

	return pModel;
}

bool CModelSwap::IsEnabled() const
{
	// Placeholder - will be replaced with actual Vars:: config
	return false;
}

std::string CModelSwap::GetModelPath() const
{
	// Placeholder - will be replaced with actual Vars:: config
	return "";
}

bool CModelSwap::SwapViewmodel() const
{
	// Placeholder - will be replaced with actual Vars:: config
	return false;
}

void CModelSwap::OnModelRender(const DrawModelState_t& pState, const ModelRenderInfo_t& pInfo, matrix3x4* pBoneToWorld)
{
	// Only swap for local player's body model (not viewmodel, not other players)
	if (!IsEnabled() || pInfo.entity_index != I::EngineClient->GetLocalPlayer())
		return;

	// Skip if this is a wearable/viewmodel
	auto pEntity = I::ClientEntityList->GetClientEntity(pInfo.entity_index)->As<CBaseEntity>();
	if (pEntity && pEntity->IsWearableVM())
		return;

	std::string sModelPath = GetModelPath();
	if (sModelPath.empty())
		return;

	// Load/cache replacement model
	model_t* pReplacementModel = LoadAndCacheModel(sModelPath);
	if (!pReplacementModel)
		return;

	// Check if bone structure is compatible (fallback on mismatch)
	// For now, we'll allow the swap and let the engine handle bone mismatches
	// In production, you'd verify bone counts match or handle remapping

	// Mark that we're swapping this frame (for state restoration)
	m_bSwappingThisFrame = true;

	// Replace the model in the render info
	// Note: pInfo is const, so we must return early and use a hook to modify it
	// This is handled by the hook in IVModelRender_DrawModelExecute
}
