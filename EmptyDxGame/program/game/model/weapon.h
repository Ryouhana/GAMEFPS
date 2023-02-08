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
	//�}�E�X�z�C�[���̉�]�ʕϐ�
	int mousewheel = 0;
	//�����e��A�ō������e��A�}�K�W�����̒e���A�}�K�W�����̍ő吔
	int ammunition = 60, maxAmmunition = 60, ammoClip = 15, maxAmmoClip = 15;
	void Initialize();
	void Update(float deltaTime);
	void Render();

	bool HandGunFlag = false;
	bool SubMachineGunFlah = false;
	bool AssaultRifleFlag = false;
private:
};