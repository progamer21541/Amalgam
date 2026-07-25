#include "ModelSwap.h"

model_t* CModelSwap::LoadAndCacheModel(const std::string& sModelPath)
{
	// If path hasn't changed and we have a cached model, return it
	if (m_sCachedModelPath == sModelPath && m_bModelValid && m_pCachedModel)
		return m_pCachedModel;

	// Clear old cache
	ClearCache();

	// Validate path is not empty
	if (sModelPath.empty())
		return nullptr;

	// Load the model using engine interfaces
	int iModelIndex = I::ModelInfo->GetModelIndex(sModelPath.c_str());
	if (iModelIndex == -1)
	{
		// Try to precache the model if it hasn't been loaded yet
		iModelIndex = I::EngineClient->LoadModel(sModelPath.c_str());
		if (iModelIndex == -1)
			return nullptr;
	}

	// Get the model_t pointer from the index
	m_pCachedModel = I::ModelInfo->GetModel(iModelIndex);
	if (!IsValidModel(m_pCachedModel))
	{
		m_pCachedModel = nullptr;
		return nullptr;
	}

	m_sCachedModelPath = sModelPath;
	m_bModelValid = true;
	return m_pCachedModel;
}

void CModelSwap::ClearCache()
{
	m_pCachedModel = nullptr;
	m_sCachedModelPath = "";
	m_bModelValid = false;
}

bool CModelSwap::IsValidModel(model_t* pModel)
{
	if (!pModel)
		return false;

	// Basic validation: model should have type info
	// In Source engine, model_t* has type field indicating model type
	return pModel != nullptr;
}

void CModelSwap::OnDrawModel(const DrawModelState_t& pState, const ModelRenderInfo_t& pInfo, matrix3x4* pBoneToWorld)
{
	// Only swap if feature is enabled
	if (!Vars::Visuals::ModelSwap::Enabled.Value)
		return;

	// Only affect the local player
	int iLocalPlayer = I::EngineClient->GetLocalPlayer();
	if (pInfo.entity_index != iLocalPlayer)
		return;

	// Get replacement model path from config
	std::string sReplacementPath = Vars::Visuals::ModelSwap::ReplacementModelPath.Value;
	if (sReplacementPath.empty())
		return;

	// Load and cache the replacement model
	model_t* pReplacementModel = LoadAndCacheModel(sReplacementPath);
	if (!pReplacementModel)
		return; // Fall back to original if invalid

	// Replace the model in the render info
	const_cast<ModelRenderInfo_t&>(pInfo).pModel = pReplacementModel;
}

void CModelSwap::Store()
{
	// Called when storing frame data; can be used for initialization
}

void CModelSwap::Reset()
{
	// Clear cached model when resetting (e.g., on map change, server shutdown)
	ClearCache();
}

bool CModelSwap::IsEnabled() const
{
	return Vars::Visuals::ModelSwap::Enabled.Value;
}

std::string CModelSwap::GetReplacementModelPath() const
{
	return Vars::Visuals::ModelSwap::ReplacementModelPath.Value;
}

bool CModelSwap::ShouldSwapViewmodel() const
{
	return Vars::Visuals::ModelSwap::SwapViewmodel.Value;
}
