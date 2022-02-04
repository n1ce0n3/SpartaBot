#include "PatternScan.h"

const char* Scan(const char* Pattern, const char* Mask)
{
    DWORD ArtificalBaseAddress = 0x10000000;
    DWORD BaseAddress = (DWORD)GetModuleHandle(NULL);
    MEMORY_BASIC_INFORMATION Mbi;
    DWORD patternLen = strlen(Mask);
    for (int i = 0; i < 0x50000000 ; i++)
    {
    
        bool PatternFound = true;

        if (VirtualQuery((LPCVOID)(ArtificalBaseAddress + i), &Mbi, sizeof(Mbi))) {
            ;
            if ((Mbi.State == MEM_COMMIT || Mbi.State == MEM_RESERVE) && (Mbi.Protect == PAGE_EXECUTE_READ) && (Mbi.Type == MEM_PRIVATE) && (Mbi.AllocationProtect == PAGE_NOACCESS)) {

                for (int j = 0; j < patternLen; j++)
                {
                    if (Mask[j] != '?' && Pattern[j] != *(char*)((DWORD)ArtificalBaseAddress + i + j))
                    {
                        PatternFound = false;
                        break;
                    }
                }

                if (PatternFound)
                {
                    return (const char*)(ArtificalBaseAddress + i);
                    break;
                }

            }
            else {
                i += Mbi.RegionSize;
            }
        }
        else {
            i += Mbi.RegionSize;
        }
    }
    return nullptr;

}

