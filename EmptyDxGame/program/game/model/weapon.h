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
	WeaponType W_type;
	Weapon();
	~Weapon() {};
	int HandGunImage = 0;
	int SubMachineGunImage = 0;
	int AssaultRifleImage = 0;

	int HandGun_Reroad = 0;
	//ƒ}ƒEƒXƒzƒC[ƒ‹‚Ì‰ñ“]—Ê•Ï”
	int mousewheel = 0;
	//Š’e–òAÅ‚Š’e–òAƒ}ƒKƒWƒ““à‚Ì’e”Aƒ}ƒKƒWƒ““à‚ÌÅ‘å”
	int ammunition = 60, maxAmmunition = 60, ammoClip = 15, maxAmmoClip = 15;
	//•â[‚·‚é‚×‚«’e–ò‚Ì•Ï”‚Æ•â[‚·‚é’e–ò‚Ì•Ï”
	int amountNeed = 0, ammoAvailable = 0;
	int debug = 0;
	int Tama_0 = 0;
	float reroad_x = 500.0, reroad_y = 400.0;
	double debug_i = 0.f;
	void Initialize();
	void Update(float deltaTime);
	void Render();

	bool HandGunFlag = false;
	bool SubMachineGunFlah = false;
	bool AssaultRifleFlag = false;
	bool GunReroad = false;
private:
};