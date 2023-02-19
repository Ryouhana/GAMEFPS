#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../gm_camera.h"
#include "Player.h"
//#include "../scene/gm_scene_play.h"

class Weapon {
public:
	enum WeaponType {
		HandGun = 1,
		SubMachineGun,
		AssaultRifle

	};

	
	Weapon();
	~Weapon() {};
	//Player* player_ = nullptr;
	
	//int ModelHandle = 0;
	
	
	struct HandGunStatus {
		int HandGunImage = 0;
		//int HandGunModelHandle = 0;
		//Š’e–òAÅ‚Š’e–òAƒ}ƒKƒWƒ““à‚Ì’e”Aƒ}ƒKƒWƒ““à‚ÌÅ‘å”
		int ammunition = 60, maxAmmunition = 60, ammoClip = 15, maxAmmoClip = 15;
		//•â[‚·‚é‚×‚«’e–ò‚Ì•Ï”‚Æ•â[‚·‚é’e–ò‚Ì•Ï”
		int amountNeed = 0, ammoAvailable = 0;
		int HandGun_Reroad = 0;
		float reroad_x = 500.0, reroad_y = 400.0;
		float reroadtime = 2.0f;
		float shoottime = 20.0f;
	};
	HandGunStatus hand_status;

	struct SubMachineGunStatus {
		int SubMachineGunImage = 0;
		//Š’e–òAÅ‚Š’e–òAƒ}ƒKƒWƒ““à‚Ì’e”Aƒ}ƒKƒWƒ““à‚ÌÅ‘å”
		int ammunition = 110, maxAmmunition = 110, ammoClip = 25, maxAmmoClip = 25;
		//•â[‚·‚é‚×‚«’e–ò‚Ì•Ï”‚Æ•â[‚·‚é’e–ò‚Ì•Ï”
		int amountNeed = 0, ammoAvailable = 0;
		int SubMachinGun_Rrroad = 0;
		float reroad_x = 500.0, reroad_y = 400.0;
		float reroadtime = 1.5f;
		float shoottime = 5.0f;
	};
	SubMachineGunStatus sub_status;

	struct AssaultRifleStatus {
		int AssaultRifleImage = 0;
		//int AssaultModelHandle = 0;
		//Š’e–òAÅ‚Š’e–òAƒ}ƒKƒWƒ““à‚Ì’e”Aƒ}ƒKƒWƒ““à‚ÌÅ‘å”
		int ammunition = 90, maxAmmunition = 90, ammoClip = 30, maxAmmoClip = 30;
		//•â[‚·‚é‚×‚«’e–ò‚Ì•Ï”‚Æ•â[‚·‚é’e–ò‚Ì•Ï”
		int amountNeed = 0, ammoAvailable = 0;
		int AssaultRifle_Reroad = 0;
		float reroad_x = 500.0, reroad_y = 400.0;
		float reroadtime = 0.8f;
		float shoottime = 8.0f;
		
	};
	AssaultRifleStatus assault_status;

	//tnl::Quaternion rot_;
	//tnl::Vector3 pos_;

	
	//•Ší‚Ì‰æ‘œ
	int HandGunImage = 0;
	int SubMachineGunImage = 0;
	int AssaultRifleImage = 0;
	int NormalWeaponImage = 0;
	//e‚ÌƒŠƒ[ƒh‰¹
	int HandGun_Reroad = 0;
	int SubMachinGun_Reroad = 0;
	int AssaultRifle_Reroad = 0;
	int NormalWeapon_Reroad = 0;
	//ƒ}ƒEƒXƒzƒC[ƒ‹‚Ì‰ñ“]—Ê•Ï”
	int mousewheel = 0;
	//Š’e–òAÅ‚Š’e–òAƒ}ƒKƒWƒ““à‚Ì’e”Aƒ}ƒKƒWƒ““à‚ÌÅ‘å”
	int ammunition = 60, maxAmmunition = 60, ammoClip = 15, maxAmmoClip = 15;
	//•â[‚·‚é‚×‚«’e–ò‚Ì•Ï”‚Æ•â[‚·‚é’e–ò‚Ì•Ï”
	int amountNeed = 0, ammoAvailable = 0;
	int debug = 0;
	int Tama_0 = 0;
	float shoottime = 0;
	float reroad_x = 500.0, reroad_y = 400.0;
	float reroadtime = 0.f;
	//float x = 0, y = 0, z = 0;
	//float angleX = 0, angleY = 0, angleZ = 0;
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
};