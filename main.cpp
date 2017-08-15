#include "F4SE/PluginAPI.h"

#include "F4SE_common/F4SE_version.h"
#include "F4SE_common/Relocation.h"
#include "F4SE_common/SafeWrite.h"


#include <shlobj.h>

IDebugLog	gLog;

PluginHandle				  g_pluginHandle = kPluginHandle_Invalid;




void InitHooks()
{
	constexpr char* configFile = ".\\Data\\F4se\\Plugins\\UnlimitedSurvivalMode.ini";
	constexpr char* settingsSection = "Settings";

	if (GetPrivateProfileInt(settingsSection, "iEnableFastTravel", 0, configFile))
	{
		UInt8 instructions[] = { 0xE9, 0xF2, 0x00, 0x00, 0x00, 0x90 };
		SafeWriteBuf(RelocAddr<uint32_t*>(0xB7D0EB).GetUIntPtr(), instructions, 6);
	}

	if (GetPrivateProfileInt(settingsSection, "iEnableConsole", 0, configFile))
	{
		//Enable console.
		SafeWrite8(RelocAddr<uint32_t*>(0x128D632).GetUIntPtr(), 0xEB);
	}
	//Restore TGM 
	if (GetPrivateProfileInt(settingsSection, "iEnableGodMode", 0, configFile))
	{
		SafeWrite8(RelocAddr<uint32_t*>(0x0E89E3A).GetUIntPtr(), 0xEB);
		SafeWrite8(RelocAddr<uint32_t*>(0x0E89D81).GetUIntPtr(), 0xEB);
		SafeWrite8(RelocAddr<uint32_t*>(0x0E9DF80).GetUIntPtr(), 0xEB);
	}
	//Enable quick save.
	if (GetPrivateProfileInt(settingsSection, "iEnableQuickSave", 0, configFile))
	{
		SafeWrite16(RelocAddr<uint32_t*>(0x128DA84).GetUIntPtr(), 0x9090);//128DA84
	}
	//Save/Load button
	if (GetPrivateProfileInt(settingsSection, "iEnableSaveLoadButton", 0, configFile))
	{
		SafeWrite16(RelocAddr<uint32_t*>(0x0B6646F).GetUIntPtr(), 0x9090);
	}

	if (GetPrivateProfileInt(settingsSection, "iAllowReenableSurvivalMode", 0, configFile))
	{
		//Allow re-enable Survival
		UInt8 nops[] = { 0x90, 0x90, 0x90, 0x90, 0x90 };
		SafeWriteBuf(RelocAddr<uint32_t*>(0x00B6656D).GetUIntPtr(), nops, sizeof(nops));
	}

	if (GetPrivateProfileInt(settingsSection, "iRestoreVanillaCompassSettings", 0, configFile))
	{
		//Restore vanilla compass settings.
		SafeWrite8(RelocAddr<uint32_t*>(0x0A39B06).GetUIntPtr(), 0xEB);
		SafeWrite8(RelocAddr<uint32_t*>(0x0A39AB3).GetUIntPtr(), 0xEB);
		SafeWrite8(RelocAddr<uint32_t*>(0x0A3A03A).GetUIntPtr(), 0xEB);
	}

	if (GetPrivateProfileInt(settingsSection, "iShowAutoSaveSettings", 0, configFile))
	{
		//enable pause menu's auto save settings.
		UInt8 codes[] = { 0xB3, 0x01, 0x90 };
		SafeWriteBuf(RelocAddr<uint32_t*>(0x0BA8013).GetUIntPtr(), codes, sizeof(codes));
	}

	if (GetPrivateProfileInt(settingsSection, "iEnableAutoSave", 0, configFile))
	{
		//enable auto save system
		SafeWrite16(RelocAddr<uint32_t*>(0x0E814D0).GetUIntPtr(), 0x9090);
	}

	if (GetPrivateProfileInt(settingsSection, "iEnableAchievement", 0, configFile))
	{
		//enable achievement.
		UInt8 codes[] = {0x48, 0x31, 0xC0, 0xC3, 0x90, 0x90};
		SafeWriteBuf(RelocAddr<uint32_t*>(0x117720).GetUIntPtr(), codes, sizeof(codes));
	}
	//isInSurvivalMode E968B0 == 6
}



extern "C"
{
	bool F4SEPlugin_Query(const F4SEInterface * f4se, PluginInfo * info)
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Fallout4\\F4SE\\UnlimitedSurvivalMode.log");
		_MESSAGE("UnlimitedSurvivalMode: %d.%d.%d", 1, 0, 1);

		// populate info structure
		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = "UnlimitedSurvivalMode";
		info->version = 1;

		// store plugin handle so we can identify ourselves later
		g_pluginHandle = f4se->GetPluginHandle();

		if (f4se->runtimeVersion != RUNTIME_VERSION_1_9_4)
		{
			MessageBox(nullptr, "UNSUPPORTED GAME VERSION.", "UnlimitedSurvivalMode", MB_OK);
			return false;
		}

		if (f4se->isEditor)
		{
			_FATALERROR("loaded in editor, marking as incompatible");
			return false;
		}

		return true;
	}


	bool F4SEPlugin_Load(const F4SEInterface * f4se)
	{
		InitHooks();
		return true;
	}

};