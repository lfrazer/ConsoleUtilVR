#pragma once

#include "RE/Skyrim.h"

namespace Papyrus
{
	using VM = RE::BSScript::IVirtualMachine;
	using StackID = RE::VMStackID;

	class ConsoleUtil
	{
	public:
		enum
		{
			kVersion = 4
		};

		// The older version of CommonLib cannot support registering papyrus functions that use std::string, so we revert back to using BSFixedString here (IMPORTANT!)
		static void ExecuteCommand(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::BSFixedString a_command);
		static void SetSelectedReference(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESObjectREFR* a_reference);
		static RE::TESObjectREFR* GetSelectedReference(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*);
		static RE::BSFixedString ReadMessage(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*);
		static void PrintMessage(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::BSFixedString a_message);
		static std::int32_t GetVersion(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*);

		static inline bool Register(RE::BSScript::IVirtualMachine* a_vm)
		{
			
			a_vm->RegisterFunction("ExecuteCommand", CLASS_NAME, &ExecuteCommand);
			a_vm->RegisterFunction("GetSelectedReference", CLASS_NAME, &GetSelectedReference);
			a_vm->RegisterFunction("SetSelectedReference", CLASS_NAME, &SetSelectedReference);
			a_vm->RegisterFunction("ReadMessage", CLASS_NAME, &ConsoleUtil::ReadMessage);
			a_vm->RegisterFunction("PrintMessage", CLASS_NAME, &ConsoleUtil::PrintMessage);
			
			a_vm->RegisterFunction("GetVersion", CLASS_NAME, &ConsoleUtil::GetVersion);

			_MESSAGE("Registered funcs for class %s", CLASS_NAME);

			return true;
		}

	private:
		static constexpr char CLASS_NAME[] = "ConsoleUtil";
	};

	inline bool Register(RE::BSScript::IVirtualMachine* a_vm)
	{
		ConsoleUtil::Register(a_vm);
		return true;
	}
}
