#include "Detour.h"

bool Hook(void* toHook, void* ourFunct, int len) {

	if (len < 5) {
		return false;
	}

	DWORD curProtection;
	VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &curProtection);

	// Calculate the "distance" we're gonna have to jump - the size of the JMP instruction
	DWORD relativeAddress = ((DWORD)ourFunct - (DWORD)toHook) - 5;

	*(BYTE*)toHook = 0xE9; // Setting The Orig Function to Opcode Jump
	*(DWORD*)((DWORD)toHook + 1) = relativeAddress; // Dereference and then typecasting a pointer and then typecasting again
	// To the variable toHook + 1 // which is are function? 

	DWORD temp;
	VirtualProtect(toHook, len, curProtection, &temp);

	return true;
}
