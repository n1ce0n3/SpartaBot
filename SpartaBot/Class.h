#include <Windows.h>

class Entity
{
public:
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
class Velocity
{
	// Note to self for some reason reclass was being weird and I had to do it this way.
public:
	char pad_0000[956]; //0x0000
	float YVelocity; //0x03BC
	char pad_03C0[4]; //0x03C0
	float XVelocity; //0x03C4
	char pad_03C8[376]; //0x03C8
};
class WeaponClass
{
public:
	char pad_0000[72]; //0x0000
	class WeaponModelClass* WeaponModel; //0x0048
	char pad_004C[56]; //0x004C
}; //Size: 0x0084
class WeaponModelClass
{
public:
	char pad_0000[8]; //0x0000
	int32_t CurrentWeapon; //0x0008
	char pad_000C[56]; //0x000C
}; //Size: 0x0044



struct InfoStruct {
	BYTE LocalPlayerBytes[6] = { 0x8B, 0x9A, 0x40, 0x03, 0x00, 0x00 };
	BYTE EntityListBytes[6] = { 0x89, 0x8A, 0x30, 0x02, 0x00, 0x00 };
	BYTE GameInputBytes[6] = { 0x8B, 0x4A, 0x34, 0x89, 0x4A, 0x2C };
	BYTE MainLoopBytes[6] = { 0x8B, 0xB0, 0x20, 0x01, 0x00, 0x00 };
	uintptr_t JumpBackAddressLocalPlayer = 0;
	uintptr_t JumpBackAddressEntityList = 0;
	uintptr_t JumpBackAddressGameInput = 0;
	uintptr_t JumpBackAddressMainLoop = 0;
	uintptr_t LocalPlayerAddress = 0;
	uintptr_t EnemyPlayerAddress = 0;
	uintptr_t GameInputAddress = 0;
}Info;

struct WeaponStruct {
	int Hammer = 0x00005356;
	int Blasters = 0x000040fb;
	int Unarmed = 0x00003D02;
	int Sword = 0x0000451C;
	int Spear = 0x0000639B;
	int Lance = 0x00004f8d;
	int Bow = 0x00006CE5;
}Weapon;

struct GameInputStruct {
	uintptr_t* CurrentGInputAddress = 0;
	int Down = 2;
	int Left = 4;
	int Right = 8;
	int Up = 33;
	int QuickAttack = 128;
	int HeavyAttack = 64;
	int Dodge = 256;
	int PickUpWeapon = 512;
	int Jump = 16;
	int Reset = 0;
}GInput;

struct BotStruct {
	int Direction = 0;
	double AbsMagX = 0;
	double AbsMagY = 0;
	double MagX = 0;
	double MagY = 0;


	// Velocity Y
	double EnemyLastPosY = 0;
	double LocalLastPosY = 0;
	bool EnemyPlayerFalling = false;
	bool LocalPlayerFalling = false;
	/******************************/
	bool DebugMode = false;
	/******************************/
	int DelayForCurrentAttack = 0;
	bool CheckIfHit = false;
	bool CanAttack = true;
	/******************************/
	bool ResetInput = false;
	bool InputReseted = false;
	bool InputResetInProgress = false;
	/******************************/
	int DelayForInstantReset = 0;
	bool InstantInputReset = false;
	/******************************/
	bool ExitThreads = false;
	/******************************/
	Entity* LocalPlayer = 0;
	Entity* EnemyPlayer = 0;
	Velocity* LP = 0;
	Velocity* EP = 0;
	/******************************/
	bool SpecialCombo = false;
}Bot;

struct UserStruct {
	bool WKey = false;
	bool AKey = false;
	bool DKey = false;
	bool SKey = false;
	SHORT W = 0x57;
	SHORT S = 0x53;
	SHORT D = 0x44;
	SHORT A = 0x41;
}User;

struct BowStruct {
	bool DidSLight = false;
}Bow;

struct SwordStruct {
	bool DLightComboStarted = false;
	double TimeForDLightToHit = 300;
}Sword;


struct GunStruct {
	bool RecoveryAttackStarted = false;
}Gun;


/*

Hammer : 00005356
Blasters : 000040A3
Unarmed/Melee : 00003CB5
Guanlets : 00007719
Sword : 000044BA
Spear : 00006306
Axe : 000071BC
Scythe : 00008495
Bow : 00006C39
Cannon : 00008D55
Katars : 00006700
GreatSword : 0000AD8C
Rocket Lance : 00004F1B
Orb : 000092A1

*/
