#pragma once
#include <windows.h>

class AntiDebug
{
public:
	inline void CheckAddress();
	inline void Routine();

	BOOL ASM_IsDebuggerPresent();
	//BOOL ASM_IsDebuggerPresent_Direct();
};