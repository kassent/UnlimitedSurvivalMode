#include "F4SE/PluginAPI.h"

#include "F4SE_common/F4SE_version.h"
#include "F4SE_common/Relocation.h"
#include "F4SE_common/SafeWrite.h"

#ifdef DEBUG
#include "F4SE_common/BranchTrampoline.h"
#endif

#include <shlobj.h>

IDebugLog						gLog;
UInt32							g_runtimeVersion = 0;
PluginHandle					g_pluginHandle = kPluginHandle_Invalid;

void InitHooks_1_9_4()
{
	constexpr char* configFile = ".\\Data\\F4se\\Plugins\\UnlimitedSurvivalMode.ini";
	constexpr char* settingsSection = "Settings";

	if (GetPrivateProfileInt(settingsSection, "iEnableFastTravel", 0, configFile))
	{
		UInt8 instructions[] = { 0xE9, 0xF2, 0x00, 0x00, 0x00, 0x90 };
		SafeWriteBuf(RelocAddr<uintptr_t>(0xB7D0EB).GetUIntPtr(), instructions, 6);
	}

	if (GetPrivateProfileInt(settingsSection, "iEnableConsole", 0, configFile))
	{
		//Enable console.
		SafeWrite8(RelocAddr<uintptr_t>(0x128D632).GetUIntPtr(), 0xEB);
	}
	//Restore TGM 
	if (GetPrivateProfileInt(settingsSection, "iEnableGodMode", 0, configFile))
	{
		SafeWrite8(RelocAddr<uintptr_t>(0x0E89E3A).GetUIntPtr(), 0xEB);
		SafeWrite8(RelocAddr<uintptr_t>(0x0E89D81).GetUIntPtr(), 0xEB);
		SafeWrite8(RelocAddr<uintptr_t>(0x0E9DF80).GetUIntPtr(), 0xEB);
	}
	//Enable quick save.
	if (GetPrivateProfileInt(settingsSection, "iEnableQuickSave", 0, configFile))
	{
		SafeWrite16(RelocAddr<uintptr_t>(0x128DA84).GetUIntPtr(), 0x9090);//128DA84
	}
	//Save/Load button
	if (GetPrivateProfileInt(settingsSection, "iEnableSaveLoadButton", 0, configFile))
	{
		SafeWrite16(RelocAddr<uintptr_t>(0x0B6646F).GetUIntPtr(), 0x9090);
	}

	if (GetPrivateProfileInt(settingsSection, "iCanReenableSurvivalMode", 0, configFile))
	{
		//Allow re-enable Survival
		UInt8 nops[] = { 0x90, 0x90, 0x90, 0x90, 0x90 };
		SafeWriteBuf(RelocAddr<uintptr_t>(0x00B6656D).GetUIntPtr(), nops, sizeof(nops));
	}

	if (GetPrivateProfileInt(settingsSection, "iShowEnemyRedDotOnCompass", 0, configFile))
	{
		//Restore vanilla compass settings.
		SafeWrite8(RelocAddr<uintptr_t>(0x0A39B06).GetUIntPtr(), 0xEB);
	}

	if (GetPrivateProfileInt(settingsSection, "iShowLocationsOnCompass", 0, configFile))
	{
		SafeWrite8(RelocAddr<uintptr_t>(0x0A39AB3).GetUIntPtr(), 0xEB);
		SafeWrite8(RelocAddr<uintptr_t>(0x0A3A03A).GetUIntPtr(), 0xEB);
	}

	if (GetPrivateProfileInt(settingsSection, "iShowAutoSaveSettings", 0, configFile))
	{
		//enable pause menu's auto save settings.
		UInt8 codes[] = { 0xB3, 0x01, 0x90 };
		SafeWriteBuf(RelocAddr<uintptr_t>(0x0BA8013).GetUIntPtr(), codes, sizeof(codes));
	}

	if (GetPrivateProfileInt(settingsSection, "iEnableAutoSave", 0, configFile))
	{
		//enable auto save system
		SafeWrite16(RelocAddr<uintptr_t>(0x0E814D0).GetUIntPtr(), 0x9090);
	}

	if (GetPrivateProfileInt(settingsSection, "iEnableAchievement", 0, configFile))
	{
		//enable achievement.
		UInt8 codes[] = { 0x48, 0x31, 0xC0, 0xC3, 0x90, 0x90 };
		SafeWriteBuf(RelocAddr<uintptr_t>(0x117720).GetUIntPtr(), codes, sizeof(codes));
	}

	if (GetPrivateProfileInt(settingsSection, "iDisablesStimpakAmmoWeight", 0, configFile))
	{
		SafeWrite16(RelocAddr<uintptr_t>(0x168CCA).GetUIntPtr(), 0x9090);
		SafeWrite8(RelocAddr<uintptr_t>(0x168D54).GetUIntPtr(), 0xEB);
	}
	//isInSurvivalMode E968B0 == 6
}


void InitHooks_1_10_20()
{
	constexpr char* configFile = ".\\Data\\F4se\\Plugins\\UnlimitedSurvivalMode.ini";
	constexpr char* settingsSection = "Settings";

	if (GetPrivateProfileInt(settingsSection, "iEnableFastTravel", 0, configFile))
	{
		//V1.10
		UInt8 instructions[] = { 0xE9, 0xF2, 0x00, 0x00, 0x00, 0x90 };
		SafeWriteBuf(RelocAddr<uintptr_t>(0xB94A8B).GetUIntPtr(), instructions, 6);
	}

	if (GetPrivateProfileInt(settingsSection, "iEnableConsole", 0, configFile))
	{
		//V1.10
		//Enable console.
		SafeWrite8(RelocAddr<uintptr_t>(0x12A9292).GetUIntPtr(), 0xEB);
	}
	//Restore TGM 
	if (GetPrivateProfileInt(settingsSection, "iEnableGodMode", 0, configFile))
	{
		//V1.10
		SafeWrite8(RelocAddr<uintptr_t>(0x0EA1BFA).GetUIntPtr(), 0xEB);
		SafeWrite8(RelocAddr<uintptr_t>(0x0EA1B41).GetUIntPtr(), 0xEB);
		SafeWrite8(RelocAddr<uintptr_t>(0x0EB5D10).GetUIntPtr(), 0xEB);
	}
	//Enable quick save.
	if (GetPrivateProfileInt(settingsSection, "iEnableQuickSave", 0, configFile))
	{
		//V1.10
		SafeWrite16(RelocAddr<uintptr_t>(0x12A96E4).GetUIntPtr(), 0x9090);//128DA84
	}
	//Save/Load button
	if (GetPrivateProfileInt(settingsSection, "iEnableSaveLoadButton", 0, configFile))
	{
		//V1.10
		SafeWrite16(RelocAddr<uintptr_t>(0x0B7DE0F).GetUIntPtr(), 0x9090);
	}

	if (GetPrivateProfileInt(settingsSection, "iCanReenableSurvivalMode", 0, configFile))
	{
		//V1.10
		//Allow re-enable Survival
		UInt8 nops[] = { 0x90, 0x90, 0x90, 0x90, 0x90 };
		SafeWriteBuf(RelocAddr<uintptr_t>(0x0B7DF0D).GetUIntPtr(), nops, sizeof(nops));
	}

	if (GetPrivateProfileInt(settingsSection, "iShowEnemyRedDotOnCompass", 0, configFile))
	{
		//V1.10
		//Restore vanilla compass settings.
		//fSurvivalPerceptionCompassBase
		//fSurvivalPerceptionCompassMult
		SafeWrite8(RelocAddr<uintptr_t>(0x0A3BC26).GetUIntPtr(), 0xEB); //A3BC26
	}

	if (GetPrivateProfileInt(settingsSection, "iShowLocationsOnCompass", 0, configFile))
	{
		//fSurvivalCompassLocationMaxDist
		SafeWrite8(RelocAddr<uintptr_t>(0x0A3BBD3).GetUIntPtr(), 0xEB); //A3BBD3
		SafeWrite8(RelocAddr<uintptr_t>(0x0A3C15A).GetUIntPtr(), 0xEB); //A3C15A
	}

	if (GetPrivateProfileInt(settingsSection, "iShowAutoSaveSettings", 0, configFile))
	{
		//V1.10
		//enable pause menu's auto save settings.
		UInt8 codes[] = { 0xB3, 0x01, 0x90 };
		SafeWriteBuf(RelocAddr<uintptr_t>(0x0BBFA53).GetUIntPtr(), codes, sizeof(codes));
	}

	if (GetPrivateProfileInt(settingsSection, "iEnableAutoSave", 0, configFile))
	{
		//V1.10
		//enable auto save system
		SafeWrite16(RelocAddr<uintptr_t>(0x0E99270).GetUIntPtr(), 0x9090);
	}

	if (GetPrivateProfileInt(settingsSection, "iEnableAchievement", 0, configFile))
	{
		//V1.10
		//enable achievement. 
		UInt8 codes[] = { 0x48, 0x31, 0xC0, 0xC3 };
		SafeWriteBuf(RelocAddr<uintptr_t>(0x117CF0).GetUIntPtr(), codes, sizeof(codes));
	}

	if (GetPrivateProfileInt(settingsSection, "iDisablesStimpakAmmoWeight", 0, configFile))
	{
		//V1.10
		SafeWrite16(RelocAddr<uintptr_t>(0x16A33A).GetUIntPtr(), 0x9090);
		SafeWrite8(RelocAddr<uintptr_t>(0x16A3C4).GetUIntPtr(), 0xEB);
	}

	//V1.10
	//pPlayer_5AC26F8
	//isInSurvivalMode EAE640 == 6
}

#ifdef DEBUG

struct ViewCasterUpdateEvent
{
	UInt32			crosshairHandler;	// 00	RefHandler
	UInt32			unk04;				// 04
	UInt32			unk08;				// 08
	UInt32			unk0C;				// 0C
	UInt64			unk10;				// 10
	UInt64			unk18;				// 18
	UInt64			unk20;				// 20
	bool			unk28;				// 28
	UInt32			unk2C;				// 2C
	bool			unk30;				// 30
	UInt64			canInteractive;		// 38
};


#include "f4se/GameReferences.h"
class CrosshairChangeHandler : public BSTEventSink<ViewCasterUpdateEvent>
{
	//sub_9E1BE0
	//80 7F 40 00 0F 84 8A 00 00 00 80 7F 38 00 8B 47 08
public:
	virtual ~CrosshairChangeHandler() { };
	virtual	EventResult	ReceiveEvent(ViewCasterUpdateEvent * evn, void * dispatcher) override
	{
		if (evn->canInteractive)
		{
			TESObjectREFR* pRef = nullptr;
			LookupREFRByHandle(&evn->crosshairHandler, &pRef);
			if (pRef != nullptr)
			{
				_MESSAGE("name: %s", CALL_MEMBER_FN(pRef, GetReferenceName)());
				pRef->handleRefObject.DecRefHandle();
			}
		}
		return kEvent_Continue;
	}
	static void Register()
	{
		RelocPtr<BSTEventDispatcher<ViewCasterUpdateEvent> *> pDispatcher = 0x5A7DAE8;//V1.10
		if (*pDispatcher != nullptr)
		{
			static auto pCrosshairHandler = new CrosshairChangeHandler();
			reinterpret_cast<BSTEventDispatcher<ViewCasterUpdateEvent> *>((uintptr_t)(*pDispatcher) + 0x10)->AddEventSink(pCrosshairHandler);
		}
		else
		{
			_MESSAGE("Can't register crosshair updata handler...");
		}
	}
};

class TESLoadGameHandler : public BSTEventSink<TESLoadGameEvent>
{
public:
	virtual ~TESLoadGameHandler() { };
	virtual	EventResult	ReceiveEvent(TESLoadGameEvent * evn, void * dispatcher) override
	{
		CrosshairChangeHandler::Register();
		return kEvent_Continue;
	}
};

RelocPtr <bool> g_isGameDataReady = 0x05A76DA4;
typedef void(*_GameDataReady_Original)(bool isReady);
RelocAddr <_GameDataReady_Original> GameDataReady_Original = 0x0082F8D0; //V1.10

void GameDataReady_Hook(bool isReady)//E8 04 23 00 00 48 8B 5C 24 58 48 8B 6C 24 60 48 8B 74 24 68
{
	(*g_isGameDataReady) = isReady;
	GetEventDispatcher<TESLoadGameEvent>()->AddEventSink(new TESLoadGameHandler());
}
//BasicEventHandler@GameScript RegisterEvents 1455DB0  33 FF 48 8B D9 48 85 C9 74 06 48 83 C1 68 EB 03 48 8B CF
#endif


extern "C"
{

	uintptr_t Init(void)
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Fallout4\\F4SE\\UnlimitedSurvivalMode.log");
		_MESSAGE("UnlimitedSurvivalMode: %d.%d.%d", 1, 2, 0);
#ifdef DEBUG
		if (!g_branchTrampoline.Create(1024 * 64))
		{
			_MESSAGE("couldn't create branch trampoline. this is fatal. skipping remainder of init process.");
			return false;
		}

		if (!g_localTrampoline.Create(1024 * 64, nullptr))
		{
			_MESSAGE("couldn't create codegen buffer. this is fatal. skipping remainder of init process.");
			return false;
		}

		g_branchTrampoline.Write6Branch(GameDataReady_Original.GetUIntPtr(), (uintptr_t)GameDataReady_Hook);
#endif
		InitHooks_1_10_20();
		return 0;
	}

	bool F4SEPlugin_Query(const F4SEInterface * f4se, PluginInfo * info)
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Fallout4\\F4SE\\UnlimitedSurvivalMode.log");
		_MESSAGE("UnlimitedSurvivalMode: %d.%d.%d", 1, 2, 0);

		// populate info structure
		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = "UnlimitedSurvivalMode";
		info->version = 1;

		// store plugin handle so we can identify ourselves later
		g_pluginHandle = f4se->GetPluginHandle();

		//g_runtimeVersion
		if (f4se->runtimeVersion < RUNTIME_VERSION_1_9_4)
		{
			MessageBox(nullptr, "UNSUPPORTED GAME VERSION.", "UnlimitedSurvivalMode", MB_OK);
			return false;
		}
		g_runtimeVersion = f4se->runtimeVersion;

		if (f4se->isEditor)
		{
			_FATALERROR("loaded in editor, marking as incompatible");
			return false;
		}

		return true;
	}


	bool F4SEPlugin_Load(const F4SEInterface * f4se)
	{
		if (g_runtimeVersion == RUNTIME_VERSION_1_9_4)
		{
			InitHooks_1_9_4();
		}
		else/* if (g_runtimeVersion == RUNTIME_VERSION_1_10_20)*/
		{
			InitHooks_1_10_20();
		}
		return true;
	}

};