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
		//�����e��A�ō������e��A�}�K�W�����̒e���A�}�K�W�����̍ő吔
		int ammunition = 60, maxAmmunition = 60, ammoClip = 15, maxAmmoClip = 15;
		//��[����ׂ��e��̕ϐ��ƕ�[����e��̕ϐ�
		int amountNeed = 0, ammoAvailable = 0;
		float reroad_x = 500.0, reroad_y = 400.0;
		float reroadtime = 2.0f;
		int HandGun_Reroad = 0;
	};
	HandGunStatus hand_status;

	struct SubMachineGunStatus {
		int SubMachineGunImage = 0;
		//�����e��A�ō������e��A�}�K�W�����̒e���A�}�K�W�����̍ő吔
		int ammunition = 110, maxAmmunition = 110, ammoClip = 25, maxAmmoClip = 25;
		//��[����ׂ��e��̕ϐ��ƕ�[����e��̕ϐ�
		int amountNeed = 0, ammoAvailable = 0;
		float reroad_x = 500.0, reroad_y = 400.0;
		float reroadtime = 3.0f;
		int SubMachinGun_Rrroad = 0;
	
	};
	SubMachineGunStatus sub_status;

	struct AssaultRifleStatus {
		int AssaultRifleImage = 0;
		//�����e��A�ō������e��A�}�K�W�����̒e���A�}�K�W�����̍ő吔
		int ammunition = 90, maxAmmunition = 90, ammoClip = 30, maxAmmoClip = 30;
		//��[����ׂ��e��̕ϐ��ƕ�[����e��̕ϐ�
		int amountNeed = 0, ammoAvailable = 0;
		float reroad_x = 500.0, reroad_y = 400.0;
		float reroadtime = 4.0f;
		int AssaultRifle_Reroad = 0;
	};
	AssaultRifleStatus assault_status;
	
	
	//����̉摜
	int HandGunImage = 0;
	int SubMachineGunImage = 0;
	int AssaultRifleImage = 0;
	int NormalWeaponImage = 0;
	//�e�̃����[�h��
	int HandGun_Reroad = 0;
	int SubMachinGun_Reroad = 0;
	int AssaultRifle_Reroad = 0;
	int NormalWeapon_Reroad = 0;
	//�}�E�X�z�C�[���̉�]�ʕϐ�
	int mousewheel = 0;
	//�����e��A�ō������e��A�}�K�W�����̒e���A�}�K�W�����̍ő吔
	int ammunition = 60, maxAmmunition = 60, ammoClip = 15, maxAmmoClip = 15;
	//��[����ׂ��e��̕ϐ��ƕ�[����e��̕ϐ�
	int amountNeed = 0, ammoAvailable = 0;
	int debug = 0;
	int Tama_0 = 0;
	float reroad_x = 500.0, reroad_y = 400.0;
	double normalreroad_time = 0;
	float reroadtime = 0.f;
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