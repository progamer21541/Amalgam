# ModelSwap Feature - Client-Side Only

## Overview
ModelSwap is a **client-side-only** feature that replaces the local player's playermodel at render time. This is purely visual and does not affect server state or other players' views.

## Features
- ✅ **Local Player Only**: Only affects your own player model rendering
- ✅ **Render-Time Replacement**: Model swap happens during draw calls, not on server
- ✅ **No Server State Changes**: Server never knows about the swap
- ✅ **Model Caching**: Loaded models are cached to improve performance
- ✅ **Fallback Handling**: Invalid models revert to original rendering

## Configuration Variables (Vars::Visuals namespace)

```cpp
Vars::Visuals::ModelSwap::Enabled      // bool - Enable/disable feature
Vars::Visuals::ModelSwap::ReplacementModelPath  // std::string - Path to model file
Vars::Visuals::ModelSwap::SwapViewmodel // bool - Also swap viewmodel (hands/weapon)
```

### Example Model Paths
```
models/player/scout/scout.mdl
models/player/soldier/soldier.mdl
models/player/pyro/pyro.mdl
```

## Implementation Details

### Model Loading
1. Model path is converted to model index via `IVModelInfo::GetModelIndex()`
2. If not found, `IVEngineClient::LoadModel()` precaches the model
3. Model pointer cached to avoid repeated lookups

### Render Interception
- Hook point: `IVModelRender::DrawModelExecute()` (virtual index 19)
- Check: `pInfo.entity_index == I::EngineClient->GetLocalPlayer()`
- Swap: Modify `ModelRenderInfo_t.pModel` before calling original

### State Management
- Each frame, swapped state is NOT preserved server-side
- Model data cached until path changes
- Falls back to original on invalid model

## Anti-Cheat Warning ⚠️

**IMPORTANT**: While ModelSwap is client-side only, be aware:

1. **VAC Detection Risk**: Some models may trigger VAC if they contain modified textures or geometry outside TF2's allowed set
2. **Server-Side Anticheat**: Community servers with anticheat plugins may detect model loading patterns
3. **Use Stock Models**: Always use official TF2 player models or stock cosmetic models
4. **Listen Servers Only**: For testing, use local listen servers (`sv_lan 1`)

**Recommendation**: Only use this feature in offline/private servers. Public server usage may result in VAC bans.

## Testing Checklist

### Step 1: Local Listen Server Setup
```
1. Launch TF2 with `-insecure` flag (disables VAC locally)
2. Load a map: `map cp_2fort`
3. Set `sv_lan 1` in console
4. Join as a player
```

### Step 2: Feature Toggle
```
1. Enable ModelSwap in menu: Visuals > ModelSwap > Enabled
2. Set model path to a valid TF2 model
   - Example: "models/player/scout/scout.mdl"
3. Watch local player model change in 3rd person view
4. Disable feature, verify model reverts
```

### Step 3: Verification
```
1. Have another player join server
2. Confirm ONLY your model changes (third-party sees original)
3. Verify server logs don't show model name changes
4. Check that player class/animation remains unchanged
5. Test with different model families (Scout, Soldier, etc.)
```

## Known Limitations

1. **Bone Structure**: Models with mismatched bone counts may animate incorrectly
   - Solution: Use models from same class family
2. **Cosmetics**: Cosmetics attached to original model may not work
   - Solution: Use cosmetics fitted to replacement model
3. **Model Size**: Very large models may cause clipping
   - Solution: Use player-sized models, avoid prop models

## Troubleshooting

**Model doesn't change:**
- Verify model path is correct and file exists in game directory
- Check model index is valid (> 0)
- Ensure feature is enabled in menu

**Animation looks wrong:**
- Check if model is from same class (Scout swapped with Scout, etc.)
- Verify bone counts match or model supports remapping

**Performance issues:**
- Model caching should prevent reload overhead
- If stuttering, check disk I/O when loading new models

## Future Enhancements

- [ ] Model path autocomplete in UI
- [ ] Bone remapping for cross-class models
- [ ] Per-cosmetic model overrides
- [ ] Model preview in main menu
- [ ] Whitelist of safe models for public servers

---

**Credits**: Implementation follows Amalgam's hook/feature architecture (MAKE_HOOK, F:: globals, Vars:: config style)
