#pragma once
#include <unordered_set>

#include "CommandTable.h"
#include "Utilities.h"
#include "GameObjects.h"
#include "Menu.hpp"


extern std::unordered_set<UInt8> g_myMods;

void Hook_Gameplay_Init(void);
void ToggleUIMessages(bool enableSpam);
void ToggleConsoleOutput(bool enable);
bool RunCommand_NS(COMMAND_ARGS, Cmd_Execute cmd);

extern DWORD g_mainThreadID;

// this returns a refID rather than a TESObjectREFR* as dropped items are non-persistent references
UInt32 GetPCLastDroppedItemRef();
TESForm* GetPCLastDroppedItem();		// returns the base object

void SetRetainExtraOwnership(bool bRetain);