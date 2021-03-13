#include "Events.h"
#include "Papyrus.h"
#include "version.h"

#ifdef SKYRIMVR
#include "SKSE/Interfaces.h"
#include "SKSE/API.h"
#define SKSEAPI APIENTRY
#endif

void MessageHandler(SKSE::MessagingInterface::Message* a_msg)
{
	switch (a_msg->type) {
	case SKSE::MessagingInterface::kDataLoaded:
		Events::Register();
		break;
	}
}

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
{
#ifdef SKYRIMVR
	SKSE::Logger::OpenRelative(FOLDERID_Documents, L"\\My Games\\Skyrim VR\\SKSE\\ConsoleUtilVR.log");
#else
	SKSE::Logger::OpenRelative(FOLDERID_Documents, L"\\My Games\\Skyrim Special Edition\\SKSE\\ConsoleUtilSSE.log");
#endif
	SKSE::Logger::SetPrintLevel(SKSE::Logger::Level::kDebugMessage);
	SKSE::Logger::SetFlushLevel(SKSE::Logger::Level::kDebugMessage);
	SKSE::Logger::UseLogStamp(true);
	SKSE::Logger::TrackTrampolineStats(true);


	_MESSAGE("ConsoleUtilVR %s", CUTL_VERSION_VERSTRING);

	a_info->infoVersion = SKSE::PluginInfo::kVersion;
	a_info->name = "ConsoleUtilVR";
	a_info->version = CUTL_VERSION_MAJOR;

	if (a_skse->IsEditor()) {
		_MESSAGE("Loaded in editor, marking as incompatible", "");
		return false;
	}

	auto ver = a_skse->RuntimeVersion();

#ifdef SKYRIMVR
	constexpr SKSE::Version RUNTIME_VR_1_4_15_1(1, 4, 15, 1);
	if (ver < RUNTIME_VR_1_4_15_1) {
#else
	if (ver < SKSE::RUNTIME_1_5_39) {
#endif
		_FATALERROR("Unsupported runtime version %s!", ver.GetString().c_str());
		return false;
	}

	return true;
}

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
	_MESSAGE("ConsoleUtilVR loaded", "");

	SKSE::Init(a_skse);

	auto messaging = SKSE::GetMessagingInterface();
	if (!messaging->RegisterListener("SKSE", MessageHandler)) {
		return false;
	}

	auto papyrus = SKSE::GetPapyrusInterface();
	if (!papyrus->Register(Papyrus::Register)) {
		_FATALERROR("Failed to register papyrus callback", "");
		return false;
	}

	return true;
}
