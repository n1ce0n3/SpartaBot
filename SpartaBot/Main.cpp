#include <Windows.h>
#include <iostream>
#include <thread>
#include "PatternScan.h"
#include "Detour.h"
#include "Class.h"




_declspec(naked) void HookLocalPlayer() {

    static DWORD Holder;
    static DWORD JumpBack;

    _asm {
        pushad
        mov Holder, edx
    }



    Info.LocalPlayerAddress = Holder;
    JumpBack = Info.JumpBackAddressLocalPlayer;

    _asm {
        popad
        mov ebx, [edx + 0x340]
        jmp JumpBack
    }
}

_declspec(naked) void HookEntityList() {

    static DWORD Holder;
    static DWORD JumpBack;

    _asm {
        pushad
        mov Holder, edx
    }

    Info.EnemyPlayerAddress = Holder;
    JumpBack = Info.JumpBackAddressEntityList;

    if (Holder != Info.LocalPlayerAddress) {
        Info.EnemyPlayerAddress = Holder;
    }


    _asm {
        popad
        mov[edx + 0x230], ecx
        jmp JumpBack
    }
}

_declspec(naked) void HookGameInput() {

    static DWORD Holder;
    static DWORD JumpBack;

    _asm {
        pushad
        mov Holder, edx
    }

    Info.GameInputAddress = Holder;
    JumpBack = Info.JumpBackAddressGameInput;


    _asm {
        popad
        mov ecx, [edx + 0x34]
        mov[edx + 0x2C], ecx
        jmp JumpBack
    }
}

_declspec(naked) void HookMainLoop() {

    static DWORD JumpBack;

    _asm {
        pushad
    }

    JumpBack = Info.JumpBackAddressMainLoop;


    if (Info.LocalPlayerAddress > 0 && Info.EnemyPlayerAddress > 0) {

        Bot.LocalPlayer = (Entity*)Info.LocalPlayerAddress;
        Bot.EnemyPlayer = (Entity*)Info.EnemyPlayerAddress;
        Bot.LP = (Velocity*)Info.LocalPlayerAddress;
        Bot.EP = (Velocity*)Info.EnemyPlayerAddress;



        GInput.CurrentGInputAddress = (uintptr_t*)(Info.GameInputAddress + 0x34);



        if (Bot.LocalPlayer != nullptr && Bot.EnemyPlayer != nullptr) {



            // And these are for checking distance which I just want the absolute value for positive>>
            //AbsMagnitudeBetweenPlayers


            Bot.AbsMagX = abs((Bot.LocalPlayer->XPos + Bot.LP->XVelocity) - (Bot.EnemyPlayer->XPos + Bot.EP->XVelocity) + 0.0166666666666667);
            Bot.AbsMagY = abs((Bot.LocalPlayer->YPos + Bot.LP->YVelocity) - (Bot.EnemyPlayer->YPos + Bot.EP->YVelocity) + 0.0166666666666667);

            // One is for checking direction which i need negative and postive for
            //MagnitudeBetweenPlayers

            Bot.MagX = ((Bot.LocalPlayer->XPos + Bot.LP->XVelocity) - (Bot.EnemyPlayer->XPos + Bot.EP->XVelocity) + 0.0166666666666667);
            Bot.MagY = ((Bot.LocalPlayer->YPos + Bot.LP->YVelocity) - (Bot.EnemyPlayer->YPos + Bot.EP->YVelocity) + 0.0166666666666667);


            // So this part is for our direction basically to make sure our character is facing the entities.
            // Before the BOT engages
            // If the magnitude between two of the chars is negative
            // My Entity Direction Should be 0 Before the BOT Starts to engage
            // If the magnitude between two of the chars is positive
            // My Entity Direction Should be 1 Before the BOT Starts to engage...


            if (Bot.MagX > 0) {
                Bot.Direction = GInput.Left;
            }
            else if (Bot.MagX < 0) {
                Bot.Direction = GInput.Right;
            }

            if (Bot.DebugMode == true) {
                std::cout << "X Pos : " << Bot.MagX << " |" << "Y Pos : " << Bot.MagY << " | (ABS) X Pos : " << Bot.AbsMagX << " |" << " (ABS) Y Pos : " << Bot.AbsMagY << std::endl;//" | Weapon : " << " | " << "Local Player In Air : " << Bot.LocalPlayer->InAir << " | Enemy Player In Air : " << Bot.EnemyPlayer->InAir << " | LP Jumps Left : " << Bot.LocalPlayer->JumpsLeft << " | Is Enemy Stunned? : " << Bot.EnemyPlayer->IsStunned << " | Is Lp Attacking : " << Bot.LocalPlayer->IsAttacking << " | GInput : " << *GInput.CurrentGInputAddress << " | CurrentWeapon : " << std::hex << Bot.LocalPlayer->PtrToWeaponClass->WeaponModel->CurrentWeapon << std::endl;
            }
            else {

                if (Bot.LocalPlayer->IsAttacking == 0 &&
                    Bot.LocalPlayer->IsStunned == 0 &&
                    Bot.EnemyPlayer->SpawnProtection == 0 &&
                    Bot.LocalPlayer->PtrToWeaponClass != nullptr &&
                    Bot.LocalPlayer->PtrToWeaponClass->WeaponModel != nullptr
                    ) {
                    // Some checks to stop undefined behavior



                    if (Bot.LocalPlayer->PtrToWeaponClass->WeaponModel->CurrentWeapon == Weapon.Sword) {


                        // DLight
                        if ((Bot.AbsMagX > 150 && Bot.AbsMagX < 360) && (Bot.AbsMagY <= 150 && Bot.AbsMagY >= 0) && Bot.LocalPlayer->InAir == 0) {

                            //&& Bot.EnemyPlayerFalling

                            if (!Bot.ResetInput && !Bot.InputResetInProgress && !Bot.InputReseted) {
                                Bot.ResetInput = true; // Starts function for reseting input
                            }
                            else if (!Bot.ResetInput && !Bot.InputResetInProgress && Bot.InputReseted) {

                                if (Bot.CanAttack) {
                                    Bot.CanAttack = false; // Basically a cooldown for the BOT

                                    std::cout << "Down Light Attack ->";


                                    *GInput.CurrentGInputAddress = (GInput.Down + Bot.Direction + GInput.QuickAttack);
                                    Bot.DelayForCurrentAttack = 300; // Just how long it usually takes for the attack to land if we hit them
                                    // ^ Needed for hit detection

                                    Bot.CheckIfHit = true; // This value enables the BOT to check if the move it through out hit

                                }



                            }



                        }

                        // JmpNear
                        if ((Bot.AbsMagX > 50 && Bot.AbsMagX < 200) && (Bot.AbsMagY > 0 && Bot.AbsMagY < 150) && Bot.EnemyPlayer->IsStunned > 0 && Bot.LocalPlayer->JumpsLeft == 0) {

                            if (!Bot.ResetInput && !Bot.InputResetInProgress && !Bot.InputReseted) {
                                Bot.ResetInput = true; // Starts function for reseting input
                            }
                            else if (!Bot.ResetInput && !Bot.InputResetInProgress && Bot.InputReseted) {

                                if (Bot.CanAttack) {
                                    Bot.CanAttack = false; // Basically a cooldown for the BOT

                                    std::cout << "Jump Near ->";
                                    *GInput.CurrentGInputAddress = (GInput.Jump);
                                    Bot.DelayForCurrentAttack = 20; // Just how long it usually takes for the attack to land if we hit them
                                    // ^ Needed for hit detection

                                    Bot.CheckIfHit = true; // This value enables the BOT to check if the move it through out hit

                                }



                            }



                        }

                        // SAir
                        if ((Bot.AbsMagX > 100 && Bot.AbsMagX < 300) && (Bot.AbsMagY > 0 && Bot.AbsMagY < 150) && Bot.EnemyPlayer->InAir > 0 && Bot.LocalPlayer->InAir > 0) {

                            if (!Bot.ResetInput && !Bot.InputResetInProgress && !Bot.InputReseted) {
                                Bot.ResetInput = true; // Starts function for reseting input
                            }
                            else if (!Bot.ResetInput && !Bot.InputResetInProgress && Bot.InputReseted) {

                                if (Bot.CanAttack) {
                                    Bot.CanAttack = false; // Basically a cooldown for the BOT

                                    std::cout << "Side Air Attack ->";
                                    *GInput.CurrentGInputAddress = (Bot.Direction + GInput.QuickAttack);
                                    Bot.DelayForCurrentAttack = 300; // Just how long it usually takes for the attack to land if we hit them
                                    // ^ Needed for hit detection

                                    Bot.CheckIfHit = true; // This value enables the BOT to check if the move it through out hit

                                }



                            }


                        }

                        // NLight
                        if ((Bot.AbsMagX > 10 && Bot.AbsMagX < 149) && (Bot.AbsMagY < 20 && Bot.AbsMagY > 0) && Bot.LocalPlayer->InAir == 0) {

                            if (!Bot.ResetInput && !Bot.InputResetInProgress && !Bot.InputReseted) {
                                Bot.ResetInput = true; // Starts function for reseting input
                            }
                            else if (!Bot.ResetInput && !Bot.InputResetInProgress && Bot.InputReseted) {

                                if (Bot.CanAttack) {
                                    Bot.CanAttack = false; // Basically a cooldown for the BOT

                                    std::cout << "Neutral Light Attack ->";
                                    *GInput.CurrentGInputAddress = (GInput.Up + Bot.Direction + GInput.QuickAttack);
                                    Bot.DelayForCurrentAttack = 100; // Just how long it usually takes for the attack to land if we hit them
                                    // ^ Needed for hit detection

                                    Bot.CheckIfHit = true; // This value enables the BOT to check if the move it through out hit

                                }



                            }

                        }


                    }


                    if (Bot.LocalPlayer->PtrToWeaponClass->WeaponModel->CurrentWeapon == Weapon.Blasters) {

                        /*
                        // DLight
                        if ((Bot.AbsMagX > 100 && Bot.AbsMagX < 280) && (Bot.AbsMagY <= 200 && Bot.AbsMagY >= 0) && Bot.LocalPlayer->InAir == 0 && Bot.EnemyPlayerFalling) {

                            if (!Bot.ResetInput && !Bot.InputResetInProgress && !Bot.InputReseted) {
                                Bot.ResetInput = true; // Starts function for reseting input
                            }
                            else if (!Bot.ResetInput && !Bot.InputResetInProgress && Bot.InputReseted) {

                                if (Bot.CanAttack) {
                                    Bot.CanAttack = false; // Basically a cooldown for the BOT

                                    std::cout << "Down Light Attack ->";
                                    *GInput.CurrentGInputAddress = (GInput.Down + Bot.Direction + GInput.QuickAttack);
                                    Bot.DelayForCurrentAttack = 200; // Just how long it usually takes for the attack to land if we hit them
                                    // ^ Needed for hit detection

                                    Bot.CheckIfHit = true; // This value enables the BOT to check if the move it through out hit

                                }



                            }



                        }

                        // SLight
                        if ( (Bot.AbsMagX >= 300 && Bot.AbsMagX <= 450) && (Bot.AbsMagY >= 0 && Bot.AbsMagY <= 150) && Bot.EnemyPlayer->InAir > 0 && Bot.LocalPlayer->InAir == 0 && (Bot.EnemyPlayerFalling == Bot.LocalPlayerFalling)) {

                            if (!Bot.ResetInput && !Bot.InputResetInProgress && !Bot.InputReseted) {
                                Bot.ResetInput = true; // Starts function for reseting input
                            }
                            else if (!Bot.ResetInput && !Bot.InputResetInProgress && Bot.InputReseted) {

                                if (Bot.CanAttack) {
                                    Bot.CanAttack = false; // Basically a cooldown for the BOT

                                    std::cout << "Side Light Attack ->";
                                    *GInput.CurrentGInputAddress = (Bot.Direction + GInput.QuickAttack);
                                    Bot.DelayForCurrentAttack = 300; // Just how long it usually takes for the attack to land if we hit them
                                    // ^ Needed for hit detection

                                    Bot.CheckIfHit = true; // This value enables the BOT to check if the move it through out hit

                                }



                            }



                        }


                        // SAir
                        if ((Bot.AbsMagX > 300 && Bot.AbsMagX < 450) && (Bot.AbsMagY > 0 && Bot.AbsMagY < 50) && Bot.EnemyPlayer->InAir > 0 && Bot.LocalPlayer->InAir > 0 && (Bot.EnemyPlayerFalling == Bot.LocalPlayerFalling)) {

                            if (!Bot.ResetInput && !Bot.InputResetInProgress && !Bot.InputReseted) {
                                Bot.ResetInput = true; // Starts function for reseting input
                            }
                            else if (!Bot.ResetInput && !Bot.InputResetInProgress && Bot.InputReseted) {

                                if (Bot.CanAttack) {
                                    Bot.CanAttack = false; // Basically a cooldown for the BOT

                                    std::cout << "Side Air Attack ->";
                                    *GInput.CurrentGInputAddress = (Bot.Direction + GInput.QuickAttack);
                                    Bot.DelayForCurrentAttack = 50; // Just how long it usually takes for the attack to land if we hit them
                                    // ^ Needed for hit detection

                                    Bot.CheckIfHit = true; // This value enables the BOT to check if the move it through out hit

                                }



                            }


                        }
                        */

                        // DAir
                        if ((Bot.AbsMagX > 0 && Bot.AbsMagX <= 200) && (Bot.MagY >= -500 && Bot.MagY <= -200) && Bot.LocalPlayer->InAir > 0 && (Bot.EnemyPlayerFalling == Bot.LocalPlayerFalling)) {

                            if (!Bot.ResetInput && !Bot.InputResetInProgress && !Bot.InputReseted) {
                                Bot.ResetInput = true; // Starts function for reseting input
                            }
                            else if (!Bot.ResetInput && !Bot.InputResetInProgress && Bot.InputReseted) {

                                if (Bot.CanAttack) {
                                    Bot.CanAttack = false; // Basically a cooldown for the BOT

                                    std::cout << "Down Air Attack ->";
                                    *GInput.CurrentGInputAddress = (GInput.Down + Bot.Direction + GInput.QuickAttack);


                                    Bot.DelayForInstantReset = 50;
                                    Bot.InstantInputReset = true;


                                    Bot.DelayForCurrentAttack = 1000; // Just how long it usually takes for the attack to land if we hit them
                                    // ^ Needed for hit detection

                                    Bot.CheckIfHit = true; // This value enables the BOT to check if the move it through out hit

                                }



                            }

                        }


                        // NLight
                        //if


                    }


                    if (Bot.LocalPlayer->PtrToWeaponClass->WeaponModel->CurrentWeapon == Weapon.Lance) {

                        //SLight
                        if ((Bot.AbsMagX > 100 && Bot.AbsMagX <= 510) && (Bot.AbsMagY <= 200 && Bot.AbsMagY >= 0) && Bot.LocalPlayer->InAir == 0 && Bot.EnemyPlayerFalling) {

                            if (!Bot.ResetInput && !Bot.InputResetInProgress && !Bot.InputReseted) {
                                Bot.ResetInput = true; // Starts function for reseting input
                            }
                            else if (!Bot.ResetInput && !Bot.InputResetInProgress && Bot.InputReseted) {

                                if (Bot.CanAttack) {
                                    Bot.CanAttack = false; // Basically a cooldown for the BOT

                                    std::cout << "Side Light Attack ->";
                                    *GInput.CurrentGInputAddress = (Bot.Direction + GInput.QuickAttack);


                                    Bot.DelayForCurrentAttack = 700; // Just how long it usually takes for the attack to land if we hit them
                                    // ^ Needed for hit detection
                                    Bot.CheckIfHit = true; // This value enables the BOT to check if the move it through out hit

                                }



                            }

                        }



                        //SAir

                    }



                }
            }
        }

    }


    _asm {
        popad
        mov esi, [eax + 0x120]
        jmp JumpBack
    }
}


void CheckHit() {
    while (true) {
        if (Bot.ExitThreads) {
            break;
        }
        Bot.LocalPlayer = (Entity*)Info.LocalPlayerAddress;
        Bot.EnemyPlayer = (Entity*)Info.EnemyPlayerAddress;


        if (Bot.CheckIfHit && !Bot.CanAttack) {
            Sleep(Bot.DelayForCurrentAttack);
            if (Bot.EnemyPlayer->IsStunned > 0) {

                // Was Hit
                std::cout << " Hit" << std::endl;
                *GInput.CurrentGInputAddress = 0;
                Bot.InputReseted = false;
            }
            else {
                // Was Not Hit
                std::cout << " Missed" << std::endl;
                *GInput.CurrentGInputAddress = 0;
                Bot.InputReseted = false;
            }
            Bot.CheckIfHit = false; // The value that allows bot to check if the attack it through out hit a player
            Bot.CanAttack = true; // Allows the bot to starting attacking again
        }
    }
}
void ResetInput() {
    while (true) {
        if (Bot.ExitThreads) {
            break;
        }

        // Reset Input
        if (Bot.ResetInput && !Bot.InputResetInProgress) {

            Bot.ResetInput = false; // Prevents undefined behavior
            Bot.InputResetInProgress = true; // Only does once per attack


            Sleep(5);

            *GInput.CurrentGInputAddress = 0; // Reset current input


            Bot.InputReseted = true; // Variable indicating wether input has been reset or not
            Bot.InputResetInProgress = false;

            std::cout << "Input Reset -> " << std::endl; // Print out we reset input.



        }
    }

}
void ImmediateInputReset() {
    while (true) {
        if (Bot.ExitThreads) {
            break;
        }

        if (Bot.InstantInputReset) {
            Bot.InstantInputReset = false; // Only does once per call basically

            Sleep(Bot.DelayForInstantReset);
            *GInput.CurrentGInputAddress = 0;

            // Bot.InputReseted = false;
            // Bot.CheckIfHit = false; // The value that allows bot to check if the attack it through out hit a player
            // Bot.CanAttack = true; // Allows the bot to starting attacking again
        }
    }
}


DWORD WINAPI MainThread(HMODULE hModule) {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    SetConsoleTitle(L"");
    SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    ShowWindow(GetConsoleWindow(), SW_NORMAL);

    std::cout << "[+]SpartaBot Initizalized" << std::endl;

    const char* LocalPlayerAddress = Scan("\x8B\x9A\x40\x03\x00\x00\x85\xDB", "xxxx??xx");
    const char* GameInputAddress = Scan("\x8B\x4A\x34\x89\x4A\x2C\x8B\x4A\x24\x89\x4A\x28\x8B\x4D\xF0", "xxxxxxxxxxxxxxx");
    const char* EntityListAddress = Scan("\x89\x8A\x30\x02\x00\x00\x8B\x4D\xC0", "xxxx??xxx");
    const char* MainLoopAddress = Scan("\x8B\xB0\x20\x01\x00\x00\x8D\x8D\x18\xFE\xFF\xFF", "xxxx??xxxxxx");




    std::cout << std::hex << "LocalPlayer -> Found " << std::hex << (DWORD)LocalPlayerAddress << std::endl;
    std::cout << std::hex << "GameInput -> Found " << std::hex << (DWORD)GameInputAddress << std::endl;
    std::cout << std::hex << "EntityList -> Found " << std::hex << (DWORD)EntityListAddress << std::endl;
    std::cout << std::hex << "MainLoop -> Found " << std::hex << (DWORD)MainLoopAddress << std::endl;



    Info.JumpBackAddressLocalPlayer = (uintptr_t)(LocalPlayerAddress + 0x6);
    Info.JumpBackAddressEntityList = (uintptr_t)(EntityListAddress + 0x6);
    Info.JumpBackAddressGameInput = (uintptr_t)(GameInputAddress + 0x6);
    Info.JumpBackAddressMainLoop = (uintptr_t)(MainLoopAddress + 0x6);


    Hook((void*)LocalPlayerAddress, HookLocalPlayer, 6);
    Hook((void*)EntityListAddress, HookEntityList, 6);
    Hook((void*)GameInputAddress, HookGameInput, 6);
    Hook((void*)MainLoopAddress, HookMainLoop, 6);


    std::thread HitDetectionThread(CheckHit);
    std::thread ResetInputThread(ResetInput);
    std::thread ResetInputThread2(ImmediateInputReset);

    while (true) {

        /*
        if (GetAsyncKeyState(User.W) > 0) {
            User.SKey = true;
        }
        else {
            User.SKey = false;
        }
        if (GetAsyncKeyState(User.A) > 0) {
            User.SKey = true;
        }
        else {
            User.SKey = false;
        }
        if (GetAsyncKeyState(User.S) > 0) {
            User.SKey = true;
        }
        else {
            User.SKey = false;
        }
        if (GetAsyncKeyState(User.D) > 0) {
            User.SKey = true;
        }
        else {
            User.SKey = false;
        }
        */



        if (GetAsyncKeyState(0x46)) {
            if (Bot.DebugMode == true) {
                Bot.DebugMode = false;
                std::cout << "[+] Debug Mode : Disabled" << std::endl;
            }
            else if (Bot.DebugMode == false) {
                Bot.DebugMode = true;
                std::cout << "[+] Debug Mode : Enabled" << std::endl;
            }

            Sleep(1000);
        }


        if (GetAsyncKeyState(VK_END)) {

            Bot.ExitThreads = true; // Terminate other Threads.




            DWORD OldProtect;
            VirtualProtect((LPVOID)LocalPlayerAddress, sizeof(LocalPlayerAddress), PAGE_EXECUTE_READWRITE, &OldProtect);
            memcpy((void*)LocalPlayerAddress, Info.LocalPlayerBytes, 6);
            VirtualProtect((LPVOID)LocalPlayerAddress, sizeof(LocalPlayerAddress), PAGE_EXECUTE_READ, &OldProtect);

            VirtualProtect((LPVOID)EntityListAddress, sizeof(EntityListAddress), PAGE_EXECUTE_READWRITE, &OldProtect);
            memcpy((void*)EntityListAddress, Info.EntityListBytes, 6);
            VirtualProtect((LPVOID)EntityListAddress, sizeof(EntityListAddress), PAGE_EXECUTE_READ, &OldProtect);

            VirtualProtect((LPVOID)GameInputAddress, sizeof(GameInputAddress), PAGE_EXECUTE_READWRITE, &OldProtect);
            memcpy((void*)GameInputAddress, Info.GameInputBytes, 6);
            VirtualProtect((LPVOID)GameInputAddress, sizeof(GameInputAddress), PAGE_EXECUTE_READ, &OldProtect);

            VirtualProtect((LPVOID)MainLoopAddress, sizeof(MainLoopAddress), PAGE_EXECUTE_READWRITE, &OldProtect);
            memcpy((void*)MainLoopAddress, Info.MainLoopBytes, 6);
            VirtualProtect((LPVOID)MainLoopAddress, sizeof(MainLoopAddress), PAGE_EXECUTE_READ, &OldProtect);

            break;
        }
    }



    FreeConsole();
    fclose(f);
    FreeLibraryAndExitThread(hModule, 0);
}


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, hModule, NULL, NULL));


    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}