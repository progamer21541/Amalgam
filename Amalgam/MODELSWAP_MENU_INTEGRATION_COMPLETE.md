# ModelSwap Feature - Complete Integration

## Menu System Files Added

### ModelSwapMenu.h
- Static class for rendering ModelSwap UI menu
- Buffer for model path input field
- Simple Draw() interface

### ModelSwapMenu.cpp
- ImGui-based menu rendering
- Model preset buttons (all 9 classes)
- Input validation and path management
- Anti-cheat warning display
- Hover tooltips for each control

## How to Integrate into Your Menu

### Option 1: Add to Existing Visuals Menu

Find your main menu file (likely `Amalgam/src/Features/ImGui/MenuBuilder.cpp` or similar) and add:

```cpp
#include "../Visuals/ModelSwap/ModelSwapMenu.h"

// In your Visuals section of the menu:
if (ImGui::BeginTabItem("Visuals"))
{
    // ... existing visuals options ...
    
    CModelSwapMenu::Draw();  // Add this line
    
    ImGui::EndTabItem();
}
```

### Option 2: Standalone in Visuals Submenu

If you have sub-menus, add a collapsible section:

```cpp
if (ImGui::CollapsingHeader("Rendering##rendering"))
{
    CModelSwapMenu::Draw();
}
```

### Option 3: Console Commands Only

If you prefer not to add UI, users can use:

```
ModelSwap_Enabled 1
ModelSwap_ReplacementModel "models/player/scout/scout.mdl"
ModelSwap_SwapViewmodel 1
```

## Build Instructions

1. **Add files to project**:
   - Add `ModelSwapMenu.h` and `ModelSwapMenu.cpp` to your Visual Studio project
   - Alternatively, ensure they're included in your build system

2. **Update includes**:
   - In your main menu builder, add: `#include "../Visuals/ModelSwap/ModelSwapMenu.h"`
   - In your header with other feature includes

3. **Link dependencies**:
   - Ensure ImGui is linked (it already is if you have existing menus)
   - ModelSwap.cpp must be compiled
   - ModelSwap_Vars.h must be included in your Vars system

4. **Compile**:
   ```bash
   # Full rebuild recommended
   msbuild Amalgam.sln /p:Configuration=Release /p:Platform=x64 /t:Rebuild
   ```

## Menu Features

✅ **Implemented**:
- Enable/Disable toggle
- Manual model path input with Enter-to-confirm
- 9 class model preset buttons (Scout, Soldier, Pyro, Demoman, Heavy, Engineer, Medic, Sniper, Spy)
- Viewmodel swap option
- Hover tooltips on all controls
- Anti-cheat warning display
- 3-column button layout for presets

## Usage Example

Once integrated, users can:

1. Open menu → Visuals tab
2. Expand "Model Swap" section
3. Toggle "Enable Model Swap"
4. Click a preset button (e.g., "Scout") OR manually enter path
5. Optionally enable "Swap Viewmodel"
6. Third-person view to see the swapped model

## File Structure

```
Amalgam/src/Features/Visuals/ModelSwap/
├── ModelSwap.h
├── ModelSwap.cpp
├── ModelSwap_Vars.h
├── ModelSwapMenu.h          ← NEW
└── ModelSwapMenu.cpp        ← NEW
```

## Testing Menu Integration

1. Launch TF2 with Amalgam loaded
2. Open menu (default: Insert key or configurable)
3. Navigate to Visuals tab
4. Find "Model Swap" section
5. Toggle enable and click a preset
6. Enter third-person to verify model changed

## Troubleshooting

### Menu section doesn't appear
- Verify ModelSwapMenu.cpp compiled successfully
- Check that `CModelSwapMenu::Draw()` was called in menu builder
- Ensure no compilation errors in output

### Presets don't work
- Check that model paths are correct for your TF2 version
- Verify Vars::Visuals::ModelSwap namespace is properly linked
- Try manual path input instead

### Text boxes not responding
- Ensure ImGui input flags are set correctly
- Check that focus is on the input field
- Try pressing Enter to confirm input

---

**Status**: ✅ Ready for integration and testing
