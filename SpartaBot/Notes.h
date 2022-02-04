#pragma once


/*
* 
                            /*
                            // Diagnoal Chase Dodge
                            if (!Gun.RecoveryAttackStarted && Bot.EnemyPlayer->Health >= 140 && (Bot.AbsMagX > 0 && Bot.AbsMagX < 450) && (Bot.MagY > 0 && Bot.MagY < 300) && Bot.LocalPlayer->InAir == 0 ) {

                                if (!Bot.ResetInput && !Bot.InputResetInProgress && !Bot.InputReseted) {
                                    Bot.ResetInput = true; // Starts function for reseting input
                                }
                                else if (!Bot.ResetInput && !Bot.InputResetInProgress && Bot.InputReseted) {

                                    if (Bot.CanAttack) {

                                        Bot.CanAttack = false;

                                        std::cout << "Diagnoal Chase Dodge ->" << std::endl;
                                        *GInput.CurrentGInputAddress = (GInput.Up + Bot.Direction + GInput.Dodge);

                                        Bot.DelayForInstantReset = 90;
                                        Bot.InstantInputReset = true; // Had to add this in due to speical moves like this
                                        Gun.RecoveryAttackStarted = true; // Allows Part Two Of Move

                                    }
                                }

                            }


                            // Recovery Part 2
                            if (Gun.RecoveryAttackStarted && Bot.EnemyPlayer->Health >= 140 && (Bot.AbsMagX > 0 && Bot.AbsMagX < 400) && (Bot.MagY > 0 && Bot.MagY < 400) && Bot.EnemyPlayer->InAir > 0  ) {

                                if (!Bot.ResetInput && !Bot.InputResetInProgress && !Bot.InputReseted) {
                                    Bot.ResetInput = true; // Starts function for reseting input
                                }
                                else if (!Bot.ResetInput && !Bot.InputResetInProgress && Bot.InputReseted) {

                                    if (Bot.CanAttack) {
                                        Bot.CanAttack = false; // Basically a cooldown for the BOT

                                        std::cout << "Recovery Attack -> P2 : ";
                                        *GInput.CurrentGInputAddress = (GInput.Up + Bot.Direction + GInput.HeavyAttack);


                                        Bot.DelayForCurrentAttack = 500; 
                                        Bot.CheckIfHit = true; 

                                        Gun.RecoveryAttackStarted = false;
                                    }



                                }

                            }
                            */



                            /*
                            // GC For DLight

                            if ((Bot.AbsMagX > 200 && Bot.AbsMagX <= 250) && (Bot.AbsMagY > 200 && Bot.AbsMagY <= 300) && Bot.LocalPlayer->InAir > 0  ) {

                                if (!Bot.ResetInput && !Bot.InputResetInProgress && !Bot.InputReseted) {
                                    Bot.ResetInput = true; // Starts function for reseting input
                                }
                                else if (!Bot.ResetInput && !Bot.InputResetInProgress && Bot.InputReseted) {

                                    if (Bot.CanAttack) {
                                        Bot.CanAttack = false;

                                        std::cout << "Gravity Cancel -> ";
                                        *GInput.CurrentGInputAddress = (GInput.Down +  GInput.Dodge + GInput.QuickAttack);
                                        Bot.DelayForCurrentAttack = 1000;
                                        Bot.CheckIfHit = true;


                                    }
                                }
                            }
                            */

                            /*
                            // The GC DLight

                            if ((Bot.AbsMagX > 0 && Bot.AbsMagX <= 250) && (Bot.AbsMagY > 0 && Bot.AbsMagY <= 250) && Bot.LocalPlayer->InAir > 0 && Bot.EnemyPlayer->InAir > 0 ) {
                                if (!Bot.ResetInput && !Bot.InputResetInProgress && !Bot.InputReseted) {
                                    Bot.ResetInput = true; // Starts function for reseting input
                                }
                                else if (!Bot.ResetInput && !Bot.InputResetInProgress && Bot.InputReseted) {

                                    if (Bot.CanAttack) {
                                        Bot.CanAttack = false; // Basically a cooldown for the BOT

                                        std::cout << " GC Down Air Attack ->";
                                        *GInput.CurrentGInputAddress = (GInput.Down + GInput.QuickAttack);
                                        Bot.DelayForCurrentAttack = 300; // Just how long it usually takes for the attack to land if we hit them
                                        // ^ Needed for hit detection

                                        Bot.CheckIfHit = true; // This value enables the BOT to check if the move it through out hit

                                    }



                                }
                            }

                            */










// Reset GInput like the game does
        /*
        if (Bot.DidAttack && GInput.CurrentGInputAddress > 0 && *GInput.CurrentGInputAddress > 0) {
            Bot.CanAttack = false; // Disabling bots ability to attack
            if (GetTickCount() > TimerForGInput) { // Delay before reseting input value
                *GInput.CurrentGInputAddress = 0;
                Bot.DidAttack = false; // Reset the if bot attacked value
                Bot.CanAttack = true; // Allowing bot to attack again
                TimerForGInput = (GetTickCount() + DelayForGInput);
            }
        }
        */


        /*
        // Determine if player is coming towards you or not basically artifical velocity
        if (LocalPlayer != nullptr && EnemyPlayer != nullptr) {

            if (GetTickCount() > UpdateLastXMag) {
                Bot.LastMagPosX = Bot.MagX;
                UpdateLastYLocal = (GetTickCount() + 5);
            }


            if (Bot.MagX > Bot.LastMagPosX) {
                // Going Away
                Bot.Towards = false;
            }
            else if (Bot.MagX < Bot.LastMagPosX) {
                // Going Towards
                Bot.Towards = true;
            }
            else if (Bot.MagX == Bot.LastMagPosX) {
                //Bot.Towards = true;
            }
        }
        */


                            // For future reference this sideair is only for the combo

                            //std::cout << "-------------------" << std::endl;
                            //std::cout << "Side Air For DLight | " << "X Pos Between Entities -> " << Bot.AbsMagnitudeBetweenPlayersX << " | Y Pos Between Entities -> " << Bot.AbsMagnitudeBetweenPlayersY << std::endl;





                           // std::cout << "-------------------" << std::endl;
                            //std::cout << "Down Light Attack | " << "X Pos Between Entities -> " << Bot.AbsMagnitudeBetweenPlayersX << " | Y Pos Between Entities -> " << Bot.AbsMagnitudeBetweenPlayersY << std::endl;


                            if (Unarmed.CanDoMove == true && (Bot.AbsMagnitudeBetweenPlayersX > 150 && Bot.AbsMagnitudeBetweenPlayersX < 350) && (Bot.AbsMagnitudeBetweenPlayersY == 0 ) ) {


                                Bot.CanAttack = false;
                                Unarmed.CanDoMove = false;


                                std::cout << "-------------------" << std::endl;
                                std::cout << "[+] Combo Started ->" << std::endl;
                                std::cout << "Down Light ->" << std::endl;

                                *GInput.CurrentGInputAddress = 0;
                                Sleep(1);


                                *GInput.CurrentGInputAddress = (Bot.Direction + GInput.Down + GInput.QuickAttack);
                                Sleep(170);

                                if (EnemyPlayer->IsStunned > 0) {
                                    std::cout << "Hit Enemy ------->" << std::endl;
                                    Unarmed.DownLightHit = true;
                                }




                                Unarmed.TimerCoolDown = true;


                                *GInput.CurrentGInputAddress = 0;


                                Bot.CanAttack = true;

                            }
                            if (Unarmed.DownLightHit == true && (Bot.AbsMagnitudeBetweenPlayersX > 0 && Bot.AbsMagnitudeBetweenPlayersX < 160) && (Bot.AbsMagnitudeBetweenPlayersY > 30 && Bot.AbsMagnitudeBetweenPlayersY < 90)) {

                                Bot.CanAttack = false;
                                Unarmed.DownLightHit = false;


                                std::cout << "-------------------" << std::endl;
                                std::cout << "Diagnol Neutral Air ->" << std::endl;


                                *GInput.CurrentGInputAddress = 0;
                                Sleep(1);


                                *GInput.CurrentGInputAddress = (GInput.Jump + GInput.Up + Bot.Direction + GInput.QuickAttack);

                                Sleep(170);

                                if (EnemyPlayer->IsStunned > 0) {
                                    std::cout << "Hit Enemy ------->" << std::endl;
                                }


                                *GInput.CurrentGInputAddress = 0;
                                Bot.CanAttack = true;

                            }
                            if ((Bot.AbsMagnitudeBetweenPlayersX > 0 && Bot.AbsMagnitudeBetweenPlayersX < 150) && (Bot.AbsMagnitudeBetweenPlayersY == 0)) {

                                // Neutral Attack

                                std::cout << "-------------------" << std::endl;
                                std::cout << "Neutral Light ->" << std::endl;


                                Bot.CanAttack = false;


                                *GInput.CurrentGInputAddress = 0;
                                Sleep(1);

                                *GInput.CurrentGInputAddress = (Bot.Direction);
                                Sleep(30);


                                *GInput.CurrentGInputAddress = (GInput.QuickAttack);

                                Sleep(200);

                                if (EnemyPlayer->IsStunned > 0) {
                                    std::cout << "Hit Enemy ------->" << std::endl;
                                }


                                *GInput.CurrentGInputAddress = 0;

                                Bot.CanAttack = true;






                           }


                            // Down Light Attack | Combo Starter
                            if (LocalPlayer->InAir == 0 && EnemyPlayer->InAir == 0 && (Bot.AbsMagnitudeBetweenPlayersX > 100 && Bot.AbsMagnitudeBetweenPlayersX < 350) && (Bot.AbsMagnitudeBetweenPlayersY == 0)) {



                            std::cout << "-------------------" << std::endl;
                            std::cout << "[+] Combo Started ->" << std::endl;
                            std::cout << "Down Light Attack ->" << std::endl;


                            BlockInput(true);


                            *GInput.CurrentGInputAddress = 0;
                            Sleep(1);


                            *GInput.CurrentGInputAddress = (Bot.Direction + GInput.Down + GInput.QuickAttack);


                            Sleep(170);

                            if (EnemyPlayer->IsStunned > 0) {
                                std::cout << "Hit Enemy ------->" << std::endl;
                                Sword.DownLightHit = true;
                            }
                            else {
                                BlockInput(false);
                            }


                            *GInput.CurrentGInputAddress = 0;

                            Sleep(100);




                        }
                            // Neutral Light Attack
                            else if (Sword.DownLightHit == false && LocalPlayer->InAir == 0 && EnemyPlayer->InAir == 0 && (Bot.AbsMagnitudeBetweenPlayersX > 0 && Bot.AbsMagnitudeBetweenPlayersX < 200) && (Bot.AbsMagnitudeBetweenPlayersY >= 0 && Bot.AbsMagnitudeBetweenPlayersY < 100)) {

                                std::cout << "-------------------" << std::endl;
                                std::cout << "Neutral Light ->" << std::endl;



                                *GInput.CurrentGInputAddress = 0;
                                Sleep(1);


                                *GInput.CurrentGInputAddress = (GInput.Up + Bot.Direction + GInput.QuickAttack);

                                Sleep(150);

                                if (EnemyPlayer->IsStunned > 0) {
                                    std::cout << "Hit Enemy ------->" << std::endl;
                                }

                                *GInput.CurrentGInputAddress = 0;


                                Sleep(950);






                            }
                            // Side Air Attack
                            else if (Sword.DownLightHit == false && LocalPlayer->InAir > 0 && EnemyPlayer->InAir > 0 && (Bot.AbsMagnitudeBetweenPlayersX > 150 && Bot.AbsMagnitudeBetweenPlayersX < 400) && (Bot.AbsMagnitudeBetweenPlayersY >= 0 && Bot.AbsMagnitudeBetweenPlayersY < 20)) {

                                std::cout << "-------------------" << std::endl;
                                std::cout << "Side Air Attack ->" << std::endl;


                                *GInput.CurrentGInputAddress = 0;
                                Sleep(1);


                                *GInput.CurrentGInputAddress = (Bot.Direction + GInput.QuickAttack);


                                Sleep(30);
                                *GInput.CurrentGInputAddress = 0;

                                Sleep(300);

                                if (EnemyPlayer->IsStunned > 0) {
                                    std::cout << "Hit Enemy ------->" << std::endl;
                                }


                                *GInput.CurrentGInputAddress = 0;

                                Sleep(600);



                            }

                            // Down Air Attack Section

                            else if (Sword.DownLightHit == false && LocalPlayer->InAir > 0 && EnemyPlayer->InAir == 0 && (Bot.AbsMagnitudeBetweenPlayersX > 0 && Bot.AbsMagnitudeBetweenPlayersX < 149) && (Bot.MagnitudeBetweenPlayersY >= -524 && Bot.MagnitudeBetweenPlayersY <= -400 )) {

                                std::cout << "-------------------" << std::endl;
                                std::cout << "Down Air Attack 1 ->" << std::endl;


                                *GInput.CurrentGInputAddress = 0;
                                Sleep(1);


                                *GInput.CurrentGInputAddress = (GInput.Down + Bot.Direction + GInput.QuickAttack);


                                Sleep(100);

                               //if (EnemyPlayer->IsStunned > 0) {
                                 //   std::cout << "Hit Enemy ------->" << std::endl;
                                //}


                                *GInput.CurrentGInputAddress = 0;

                                Sleep(700);



                            }






                            else if (Sword.DownLightHit == false && LocalPlayer->InAir > 0 && EnemyPlayer->InAir > 0 && (Bot.AbsMagnitudeBetweenPlayersX > 0 && Bot.AbsMagnitudeBetweenPlayersX < 149) && (Bot.MagnitudeBetweenPlayersY > -450 && Bot.MagnitudeBetweenPlayersY <= 0)) {

                            std::cout << "-------------------" << std::endl;
                            std::cout << "Down Air Attack 2 ->" << std::endl;


                            *GInput.CurrentGInputAddress = 0;
                            Sleep(1);


                            *GInput.CurrentGInputAddress = (GInput.Down + Bot.Direction + GInput.QuickAttack);


                            Sleep(100);

                            //if (EnemyPlayer->IsStunned > 0) {
                              //   std::cout << "Hit Enemy ------->" << std::endl;
                             //}


                            *GInput.CurrentGInputAddress = 0;

                            Sleep(700);



                            }

                            // End of Section


                            // Neutral Air Attack
                            else if (Sword.DownLightHit == false && LocalPlayer->InAir > 0 && (Bot.AbsMagnitudeBetweenPlayersX > 0 && Bot.AbsMagnitudeBetweenPlayersX < 149) && (Bot.MagnitudeBetweenPlayersY >= 0 && Bot.MagnitudeBetweenPlayersY > 100)) {

                                std::cout << "-------------------" << std::endl;
                                std::cout << "Neutral Air Attack ->" << std::endl;


                                *GInput.CurrentGInputAddress = 0;
                                Sleep(1);


                                *GInput.CurrentGInputAddress = (GInput.Up + Bot.Direction + GInput.QuickAttack);


                                Sleep(100);


                                *GInput.CurrentGInputAddress = 0;

                                Sleep(700);



                            }



                            if (Sword.DownLightHit == true) {
                                if ((Bot.AbsMagnitudeBetweenPlayersY > 100 && Bot.AbsMagnitudeBetweenPlayersY < 150) && EnemyPlayer->IsStunned > 0 && LocalPlayer->JumpsLeft == 0) {


                                    std::cout << "Jump Near ->" << std::endl;

                                    *GInput.CurrentGInputAddress = 0;
                                    Sleep(1);
                                    *GInput.CurrentGInputAddress = (GInput.Jump);
                                    Sleep(50);
                                    *GInput.CurrentGInputAddress = 0;


                                }
                                if ((Bot.AbsMagnitudeBetweenPlayersX > 100 && Bot.AbsMagnitudeBetweenPlayersX < 200) && (Bot.AbsMagnitudeBetweenPlayersY < 150) && EnemyPlayer->IsStunned > 0 && LocalPlayer->JumpsLeft == 1) {



                                    std::cout << "Side Air For DLight Into SAir ->" << std::endl;



                                    *GInput.CurrentGInputAddress = 0;
                                    Sleep(1);


                                    *GInput.CurrentGInputAddress = (Bot.Direction + GInput.QuickAttack);
                                    Sleep(30);


                                    *GInput.CurrentGInputAddress = 0;
                                    Sword.DownLightHit = false;



                                }
                            }

        // CoolDowns


        /*
        if (Sword.CanDoMove == false) {

            if (GetTickCount() > Timer) {
                Sword.CanDoMove = true;
                Sword.TimerCoolDown = false;
                Timer = (GetTickCount() + (1000 * Delay));
            }

        }


        if (Bow.DidSLight) {
            Sleep(10); // If still true after certain amount of time then change to false
            if (Bow.DidSLight) {
                Bow.DidSLight = false;
            }
        }
              if (Bot.DidAttack && GInput.CurrentGInputAddress > 0 && *GInput.CurrentGInputAddress > 0) {
            Bot.CanAttack = false; // Disabling bots ability to attack
            Sleep(10); // Delay before reseting input value
            *GInput.CurrentGInputAddress = 0;
            Bot.DidAttack = false; // Reset the if bot attacked value
            Bot.CanAttack = true; // Allowing bot to attack again
        }

        if (Unarmed.CanDoMove == false) {

            if (GetTickCount() > Timer2) {
                Unarmed.CanDoMove = true;
                Unarmed.TimerCoolDown = false;
                Timer2 = (GetTickCount() + (1000 * Delay));
            }




        }

            char pad_0000[168]; //0x0000
    int32_t IsAttacking; //0x00A8
    char pad_00AC[48]; //0x00AC
    int32_t DirectionOfEntity; //0x00DC
    char pad_00E0[28]; //0x00E0
    int32_t InAir; //0x00FC
    char pad_0100[148]; //0x0100
    int32_t IsStunned; //0x0194
    char pad_0198[48]; //0x0198
    int32_t JumpsLeft; //0x01C8
    char pad_01CC[116]; //0x01CC
    int32_t OnEdgeOfMap; //0x0240
    int32_t SpawnProtection; //0x0244 If not equal to zero entity is protected
    char pad_0248[192]; //0x0248
    class WeaponClass* PtrToWeaponClass; //0x0308
    char pad_030C[172]; //0x030C
    double YPos; //0x03B8
    double XPos; //0x03C0
    char pad_03C8[96]; //0x03C8
    double Health; //0x0428
    char pad_0430[1344]; //0x0430
};

        */



        /*
void CheckLocalVeloY() {
    while (true) {
        if (Bot.ExitThreads) {
            break;
        }

        Bot.LocalPlayer = (Entity*)Info.LocalPlayerAddress;
        Bot.EnemyPlayer = (Entity*)Info.EnemyPlayerAddress;

        // Determine if players is going down or up basically artifical velocity
        if (Bot.LocalPlayer != nullptr && Bot.LocalPlayer->YPos > 0) {
            // Artifically Velocity Logic

            // Save old y position value determine if entity going up or down based on comparison
            Bot.LocalLastPosY = Bot.LocalPlayer->YPos; // Save Last Y and see if it's increasing or decrasing
            Sleep(10);
            if (Bot.LocalPlayer->YPos > Bot.LocalLastPosY) {
                // Going Up
                Bot.LocalPlayerFalling = false;
            }
            else if (Bot.LocalPlayer->YPos < Bot.LocalLastPosY) {
                // Going Down
                Bot.LocalPlayerFalling = true;
            }
            else if (Bot.LocalPlayer->YPos == Bot.LocalLastPosY) {
                // Hasn't moved
                Bot.LocalPlayerFalling = true;
            }
        }
    }
}
void CheckEnemyVeloY() {
    while (true) {
        if (Bot.ExitThreads) {
            break;
        }

        Bot.LocalPlayer = (Entity*)Info.LocalPlayerAddress;
        Bot.EnemyPlayer = (Entity*)Info.EnemyPlayerAddress;

        if (Bot.EnemyPlayer != nullptr && Bot.EnemyPlayer->YPos > 0) {
            // Artifically Velocity Logic
            // Save old y position value determine if entity going up or down based on comparison
            Bot.EnemyLastPosY = Bot.EnemyPlayer->YPos; // Save Last Y and see if it's increasing or decrasing
            Sleep(10);
            if (Bot.EnemyPlayer->YPos > Bot.EnemyLastPosY) {
                // Going Up
                Bot.EnemyPlayerFalling = false;
            }
            else if (Bot.EnemyPlayer->YPos < Bot.EnemyLastPosY) {
                // Going Down
                Bot.EnemyPlayerFalling = true;
            }
            else if (Bot.EnemyPlayer->YPos == Bot.EnemyLastPosY) {
                // Hasn't moved
                Bot.EnemyPlayerFalling = true;
            }
        }
    }
}









            HitDetectionThread.join();
            //CheckLocalYVelocityThread.join();
            //CheckEnemyYVelocityThread.join();




                        //Bot.MagX = (Bot.LocalPlayer->XPos - Bot.EnemyPlayer->XPos);
            //Bot.MagY = (Bot.LocalPlayer->YPos - Bot.EnemyPlayer->YPos);

/*
void CheckLocalVeloY() {
    while (true) {
        if (Bot.ExitThreads) {
            break;
        }

        Bot.LocalPlayer = (Entity*)Info.LocalPlayerAddress;
        Bot.EnemyPlayer = (Entity*)Info.EnemyPlayerAddress;

        // Determine if players is going down or up basically artifical velocity
        if (Bot.LocalPlayer != nullptr && Bot.LocalPlayer->YPos > 0) {
            // Artifically Velocity Logic

            // Save old y position value determine if entity going up or down based on comparison
            Bot.LocalLastPosY = Bot.LocalPlayer->YPos; // Save Last Y and see if it's increasing or decrasing
            Sleep(10);
            if (Bot.LocalPlayer->YPos > Bot.LocalLastPosY  ) {
                // Going Up
                Bot.LocalPlayerFalling = false;
            }
            else if (Bot.LocalPlayer->YPos < Bot.LocalLastPosY  ) {
                // Going Down
                Bot.LocalPlayerFalling = true;
            }
            else if (Bot.LocalPlayer->YPos == Bot.LocalLastPosY) {
                // Hasn't moved
                Bot.LocalPlayerFalling = true;
            }
        }
    }
}
void CheckEnemyVeloY() {
    while (true) {
        if (Bot.ExitThreads) {
            break;
        }

        Bot.LocalPlayer = (Entity*)Info.LocalPlayerAddress;
        Bot.EnemyPlayer = (Entity*)Info.EnemyPlayerAddress;

        if (Bot.EnemyPlayer != nullptr && Bot.EnemyPlayer->YPos > 0) {
            // Artifically Velocity Logic
            // Save old y position value determine if entity going up or down based on comparison
            Bot.EnemyLastPosY = Bot.EnemyPlayer->YPos; // Save Last Y and see if it's increasing or decrasing
            Sleep(10);
            if (Bot.EnemyPlayer->YPos > Bot.EnemyLastPosY ) {
                // Going Up
                Bot.EnemyPlayerFalling = false;
            }
            else if (Bot.EnemyPlayer->YPos < Bot.EnemyLastPosY ) {
                // Going Down
                Bot.EnemyPlayerFalling = true;
            }
            else if (Bot.EnemyPlayer->YPos == Bot.EnemyLastPosY) {
                // Hasn't moved
                Bot.EnemyPlayerFalling = true;
            }
        }
    }
}
*/
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

*/
