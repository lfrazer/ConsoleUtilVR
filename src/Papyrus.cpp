#include "Papyrus.h"

namespace Papyrus
{

	void ConsoleUtil::ExecuteCommand(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::BSFixedString a_command)
	{
		const auto scriptFactory = RE::IFormFactory::GetConcreteFormFactoryByType<RE::Script>();
		const auto script = scriptFactory ? scriptFactory->Create() : nullptr;
		if (script) {
			const auto selectedRef = RE::Console::GetSelectedRef();
			script->SetCommand(a_command);
			script->CompileAndRun(selectedRef.get());
			delete script;
		}
	}

	RE::TESObjectREFR* ConsoleUtil::GetSelectedReference(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*)
	{
		const auto selectedRef = RE::Console::GetSelectedRef();
		return selectedRef.get();
	}

	void ConsoleUtil::SetSelectedReference(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_reference)
	{
		using Message = RE::UI_MESSAGE_TYPE;

		if (a_reference) {
			const auto factory = RE::MessageDataFactoryManager::GetSingleton();
			const auto intfcStr = RE::InterfaceStrings::GetSingleton();
			const auto creator =
				factory && intfcStr ?
				factory->GetCreator<RE::ConsoleData>(intfcStr->consoleData) :
				nullptr;

			const auto consoleData = creator ? creator->Create() : nullptr;
			const auto msgQ = RE::UIMessageQueue::GetSingleton();
			if (consoleData && msgQ) {
				consoleData->type = static_cast<RE::ConsoleData::DataType>(1);
				consoleData->pickRef = a_reference->CreateRefHandle();
				msgQ->AddMessage(intfcStr->console, Message::kUpdate, consoleData);
			}
		}
		else {
			const auto ui = RE::UI::GetSingleton();
			const auto console = ui ? ui->GetMenu<RE::Console>() : nullptr;
			if (console) {
				const RE::ObjectRefHandle null;
				console->SetSelectedRef(null);
			}
		}
	}

	RE::BSFixedString ConsoleUtil::ReadMessage(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*)
	{
		auto consoleManager = RE::ConsoleLog::GetSingleton();
		return consoleManager ? consoleManager->lastMessage : "";
	}

	void ConsoleUtil::PrintMessage(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::BSFixedString a_message)
	{
		const auto log = RE::ConsoleLog::GetSingleton();
		if (log) {
			log->Print(a_message.c_str());
		}
	}

	std::int32_t ConsoleUtil::GetVersion(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*)
	{
		return kVersion;
	}

}