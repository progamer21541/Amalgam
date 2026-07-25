// This snippet integrates into IVModelRender_DrawModelExecute.cpp
// Insert this code after the Chams and Glow checks (around line 25)

/*
ADD THIS TO: Amalgam/src/Hooks/IVModelRender_DrawModelExecute.cpp

INSERTION POINT (after line 25, after Glow checks):

	// ModelSwap: Local player model replacement
	if (pInfo.entity_index == I::EngineClient->GetLocalPlayer())
	{
		auto pEntity = I::ClientEntityList->GetClientEntity(pInfo.entity_index)->As<CBaseEntity>();
		if (pEntity && !pEntity->IsWearableVM() && F::ModelSwap.IsEnabled())
		{
			std::string sModelPath = F::ModelSwap.GetModelPath();
			if (!sModelPath.empty())
			{
				int iModelIndex = I::ModelInfo->GetModelIndex(sModelPath.c_str());
				if (iModelIndex <= 0)
				{
					I::EngineClient->LoadModel(sModelPath.c_str());
					iModelIndex = I::ModelInfo->GetModelIndex(sModelPath.c_str());
				}

				if (iModelIndex > 0)
				{
					model_t* pReplacementModel = I::ModelInfo->GetModel(iModelIndex);
					if (pReplacementModel)
					{
						// Create a modified copy of pInfo with the replacement model
						ModelRenderInfo_t modifiedInfo = pInfo;
						modifiedInfo.pModel = pReplacementModel;
						
						// Call original with swapped model
						return CALL_ORIGINAL(rcx, pState, modifiedInfo, pBoneToWorld);
					}
				}
			}
		}
	}
*/
