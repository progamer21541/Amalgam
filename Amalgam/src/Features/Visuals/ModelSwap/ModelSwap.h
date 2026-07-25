#pragma once
#include "../../../SDK/SDK.h"

class CModelSwap
{
private:
	// Cached model data
	int m_iModelIndex = -1;
	model_t* m_pCachedModel = nullptr;
	std::string m_sLastModelPath = "";

	// State management
	bool m_bInitialized = false;
	int m_iLastCheckFrame = -1;

	// Helper methods
	model_t* LoadAndCacheModel(const std::string& sModelPath);
	void ClearCache();
	bool IsValidModel(model_t* pModel) const;

public:
	// Feature control
	void OnModelRender(const DrawModelState_t& pState, const ModelRenderInfo_t& pInfo, matrix3x4* pBoneToWorld);

	// Lifecycle
	void Init();
	void Shutdown();
	void Reset();

	// Config accessors (will be hooked via Vars::Visuals namespace)
	bool IsEnabled() const;
	std::string GetModelPath() const;
	bool SwapViewmodel() const;

	bool m_bSwappingThisFrame = false;
};

ADD_FEATURE(CModelSwap, ModelSwap);
