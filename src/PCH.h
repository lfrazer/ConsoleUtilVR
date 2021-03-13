#pragma once

#include "ForceInclude.h"
#include "RE/Skyrim.h"
#include "REL/Relocation.h"
#ifndef SKYRIMVR
#include "SKSE/SKSE.h"
#else
#include "SKSE/Logger.h"
#endif

#include "RE/Skyrim.h"


#include <memory>
#include <string>
#include <typeinfo>


using namespace std::literals;


#define DLLEXPORT __declspec(dllexport)
