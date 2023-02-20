#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../gm_camera.h"
#include "Player.h"


class Weapon {
public:
	enum WeaponType {
		HandGun = 1,
		SubMachineGun,
		AssaultRifle

	};

	
	Weapon();
	~Weapon() {};
	
	struct HandGunStatus {
		int HandGunImage = 0;
		int HandGunModelHandle = 0;
		//所持弾薬、最高所持弾薬、マガジン内の弾数、マガジン内の最大数
		int ammunition = 60, maxAmmunition = 60, ammoClip = 15, maxAmmoClip = 15;
		//補充するべき弾薬の変数と補充する弾薬の変数
		int amountNeed = 0, ammoAvailable = 0;
		int HandGun_Reroad = 0;
		float reroad_x = 500.0, reroad_y = 400.0;
		float reroadtime = 2.0f;
		float shoottime = 20.0f;
		//ハンドガン画像の位置と大きさの変数
		int weapon_x = 775;
		int weapon_y = 720;
		float weapon_scale = 0.15f;
	};
	HandGunStatus hand_status;

	struct SubMachineGunStatus {
		int SubMachineGunImage = 0;
		//所持弾薬、最高所持弾薬、マガジン内の弾数、マガジン内の最大数
		int ammunition = 110, maxAmmunition = 110, ammoClip = 25, maxAmmoClip = 25;
		//補充するべき弾薬の変数と補充する弾薬の変数
		int amountNeed = 0, ammoAvailable = 0;
		int SubMachinGun_Rrroad = 0;
		float reroad_x = 500.0, reroad_y = 400.0;
		float reroadtime = 1.5f;
		float shoottime = 5.0f;
		//サブマシンガン画像の位置と大きさの変数
		int weapon_x = 775;
		int weapon_y = 720;
		float weapon_scale = 0.15f;
	};
	SubMachineGunStatus sub_status;

	struct AssaultRifleStatus {
		int AssaultRifleImage = 0;
		int AssaultModelHandle = 0;
		//所持弾薬、最高所持弾薬、マガジン内の弾数、マガジン内の最大数
		int ammunition = 90, maxAmmunition = 90, ammoClip = 30, maxAmmoClip = 30;
		//補充するべき弾薬の変数と補充する弾薬の変数
		int amountNeed = 0, ammoAvailable = 0;
		int AssaultRifle_Reroad = 0;
		float reroad_x = 500.0, reroad_y = 400.0;
		float reroadtime = 0.8f;
		float shoottime = 8.0f;
		//アサルトライフル画像の位置と大きさの変数
		int weapon_x = 725;
		int weapon_y = 720;
		float weapon_scale = 0.08f;
		
	};
	AssaultRifleStatus assault_status;

	tnl::Quaternion rot_;
	tnl::Vector3 pos_;

	
	//武器の画像
	int HandGunImage = 0;
	int SubMachineGunImage = 0;
	int AssaultRifleImage = 0;
	int NormalWeaponImage = 0;
	//銃のリロード音
	int HandGun_Reroad = 0;
	int SubMachinGun_Reroad = 0;
	int AssaultRifle_Reroad = 0;
	int NormalWeapon_Reroad = 0;
	//マウスホイールの回転量変数
	int mousewheel = 0;
	//所持弾薬、最高所持弾薬、マガジン内の弾数、マガジン内の最大数
	int ammunition = 60, maxAmmunition = 60, ammoClip = 15, maxAmmoClip = 15;
	//補充するべき弾薬の変数と補充する弾薬の変数
	int amountNeed = 0, ammoAvailable = 0;
	int debug = 0;
	int Tama_0 = 0;
	//武器画像の位置と大きさの変数
	int weapon_x = 0;
	int weapon_y = 0;
	int demo_assaultammunition = 0, demo_assaultammoClip = 0;
	int demo_subammunition = 0, demo_subammoClip = 0;
	int demo_handammunition = 0, demo_handammoClip = 0;
	float weapon_scale = 0.f;
	float shoottime = 0.f;
	float reroad_x = 500.0f, reroad_y = 400.0f;
	float reroadtime = 0.f;
	float x = 0.f, y = 0.f, z = 0.f;
	float angleX = 0.f, angleY = 0.f, angleZ = 0.f;
	double normalreroad_time = 0;
	void Initialize();
	void Update(float deltaTime);
	void Render();
	void SwitchWeapon(WeaponType weapontype);
	
	bool HandGunFlag = false;
	bool SubMachineGunFlah = false;
	bool AssaultRifleFlag = false;
	bool GunReroad = false;
private:
	GmCamera* weapon = nullptr;
};