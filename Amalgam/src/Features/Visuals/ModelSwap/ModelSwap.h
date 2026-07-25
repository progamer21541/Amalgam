#pragma once
#include "../../../SDK/SDK.h"

class CModelSwap
{
private:
	// Cached model data
	model_t* m_pCachedModel = nullptr;
	std::string m_sCachedModelPath = "";
	bool m_bModelValid = false;

	// Helper functions
	model_t* LoadAndCacheModel(const std::string& sModelPath);
	void ClearCache();
	bool IsValidModel(model_t* pModel);

public:
	void OnDrawModel(const DrawModelState_t& pState, const ModelRenderInfo_t& pInfo, matrix3x4* pBoneToWorld);
	void Store();
	void Reset();

	// Configuration getters for menu integration
	bool IsEnabled() const;
	std::string GetReplacementModelPath() const;
	bool ShouldSwapViewmodel() const;
};

ADD_FEATURE(CModelSwap, ModelSwap);
