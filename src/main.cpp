#include "Events.h"
#include "Papyrus.h"
#include "version.h"

#include "RE/Skyrim.h"
#include "SKSE/API.h"


namespace
{
	void MessageHandler(SKSE::MessagingInterface::Message* a_msg)
	{
		switch (a_msg->type) {
		case SKSE::MessagingInterface::kDataLoaded:
			auto ui = RE::UI::GetSingleton();
			ui->AddEventSink(Events::MenuOpenCloseEventHandler::GetSingleton());
			_MESSAGE("Registered menu open close event sink");
			break;
		}
	}
}


extern "C" {
	bool SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
	{
		SKSE::Logger::OpenRelative(FOLDERID_Documents, L"\\My Games\\Skyrim Special Edition\\SKSE\\ConsoleUtilSSE.log");
		SKSE::Logger::SetPrintLevel(SKSE::Logger::Level::kDebugMessage);
		SKSE::Logger::SetFlushLevel(SKSE::Logger::Level::kDebugMessage);
		SKSE::Logger::UseLogStamp(true);

		_MESSAGE("ConsoleUtilSSE v%s", CUTL_VERSION_VERSTRING);

		a_info->infoVersion = SKSE::PluginInfo::kVersion;
		a_info->name = "ConsoleUtilSSE";
		a_info->version = CUTL_VERSION_MAJOR;

		if (a_skse->IsEditor()) {
			_FATALERROR("Loaded in editor, marking as incompatible!");
			return false;
		}

		auto ver = a_skse->RuntimeVersion();
		if (ver <= SKSE::RUNTIME_1_5_39) {
			_FATALERROR("Unsupported runtime version %s!", ver.GetString().c_str());
			return false;
		}

		return true;
	}


	bool SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
	{
		_MESSAGE("ConsoleUtilSSE loaded");

		if (!SKSE::Init(a_skse)) {
			return false;
		}

		auto messaging = SKSE::GetMessagingInterface();
		if (!messaging->RegisterListener("SKSE", MessageHandler)) {
			return false;
		}

		auto papyrus = SKSE::GetPapyrusInterface();
		if (!papyrus->Register(Papyrus::Register)) {
			_FATALERROR("Failed to register papyrus callback!");
			return false;
		}

		return true;
	}
};
