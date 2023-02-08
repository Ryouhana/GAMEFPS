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
	int HandGunImage = 0;
	int SubMachineGunImage = 0;
	int AssaultRifleImage = 0;
	//マウスホイールの回転量変数
	int mousewheel = 0;
	//所持弾薬、最高所持弾薬、マガジン内の弾数、マガジン内の最大数
	int ammunition = 60, maxAmmunition = 60, ammoClip = 15, maxAmmoClip = 15;
	void Initialize();
	void Update(float deltaTime);
	void Render();

	bool HandGunFlag = false;
	bool SubMachineGunFlah = false;
	bool AssaultRifleFlag = false;
private:
};