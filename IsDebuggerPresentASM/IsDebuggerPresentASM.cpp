#include <windows.h>
#include <winternl.h>
#include "IsDebuggerPresentASM.hpp"
#include <iostream>

using namespace std;

int main(void)
{
    AntiDebug ad;
    ad.CheckAddress();
    ad.Routine();
}

inline void AntiDebug::CheckAddress()
{
    PTEB pTeb;
    PPEB pPeb;

    __asm
    {
        mov eax, dword ptr fs : [0x18] // TEB
        lea ebx, [eax]
        mov pTeb, ebx
        mov eax, dword ptr ds : [eax + 0x30] // PEB
        lea ebx, [eax]
        mov pPeb, ebx
    }

    cout << "TEB: " << "0x" << pTeb << endl << "PEB: " << "0x" << pPeb << "\n\n";
}

inline void AntiDebug::Routine()
{
    const int delay = 1000;

    while (true) {
        if (ASM_IsDebuggerPresent()) {
            cout << "Detected" << endl;
        }
        else {
            cout << "Undetected" << endl;
        }
        Sleep(delay);
    }
}

BOOL AntiDebug::ASM_IsDebuggerPresent()
{
    BOOL beingDebugged = FALSE;

    __asm
    {
        mov eax, dword ptr fs:[0x18] // TEB
        mov eax, dword ptr ds:[eax+0x30] // PEB
        movzx eax, byte ptr ds:[eax+0x2] // beingDebugged
        mov beingDebugged, eax
    }
    return beingDebugged;
}

/*
BOOL ASM_IsDebuggerPresent_Direct()
{
    BOOL beingDebugged = FALSE;

    __asm
    {
        mov eax, dword ptr ds : [0x30] // PEB
        movzx eax, byte ptr ds : [eax + 0x2] // beingDebugged
        mov beingDebugged, eax
    }
    return beingDebugged;
}
*/