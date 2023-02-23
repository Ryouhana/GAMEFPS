#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../gm_camera.h"
#include "Player.h"
#include "../scene/gm_scene_base.h"
#include "../model/gm_model.h"
class Base;
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
	
		//�����e��A�ō������e��A�}�K�W�����̒e���A�}�K�W�����̍ő吔
		int ammunition = 60, maxAmmunition = 60, ammoClip = 15, maxAmmoClip = 15;
		//��[����ׂ��e��̕ϐ��ƕ�[����e��̕ϐ�
		int amountNeed = 0, ammoAvailable = 0;
		int HandGun_Reroad = 0;
		float reroad_x = 500.0, reroad_y = 400.0;
		float reroadtime = 2.0f;
		float shoottime = 20.0f;
		//�n���h�K���摜�̈ʒu�Ƒ傫���̕ϐ�
		int weapon_x = 775;
		int weapon_y = 720;
		float weapon_scale = 0.15f;
		float bang_x = 42.9, bang_y = -28.6f, bang_z = 78.1f;
	};
	HandGunStatus hand_status;

	struct SubMachineGunStatus {
		int SubMachineGunImage = 0;
		
		//�����e��A�ō������e��A�}�K�W�����̒e���A�}�K�W�����̍ő吔
		int ammunition = 110, maxAmmunition = 110, ammoClip = 25, maxAmmoClip = 25;
		//��[����ׂ��e��̕ϐ��ƕ�[����e��̕ϐ�
		int amountNeed = 0, ammoAvailable = 0;
		int SubMachinGun_Rrroad = 0;
		float reroad_x = 500.0, reroad_y = 400.0;
		float reroadtime = 1.5f;
		float shoottime = 5.0f;
		//�T�u�}�V���K���摜�̈ʒu�Ƒ傫���̕ϐ�
		int weapon_x = 775;
		int weapon_y = 720;
		float weapon_scale = 0.15f;
		float bang_x = 42.9, bang_y = -28.6f, bang_z = 78.1f;
	};
	SubMachineGunStatus sub_status;

	struct AssaultRifleStatus {
		int AssaultRifleImage = 0;
		int AssaultModelHandle = 0;
		
		//�����e��A�ō������e��A�}�K�W�����̒e���A�}�K�W�����̍ő吔
		int ammunition = 90, maxAmmunition = 90, ammoClip = 30, maxAmmoClip = 30;
		//��[����ׂ��e��̕ϐ��ƕ�[����e��̕ϐ�
		int amountNeed = 0, ammoAvailable = 0;
		int AssaultRifle_Reroad = 0;
		float reroad_x = 500.0, reroad_y = 400.0;
		float reroadtime = 0.8f;
		float shoottime = 8.0f;
		//�A�T���g���C�t���摜�̈ʒu�Ƒ傫���̕ϐ�
		int weapon_x = 725;
		int weapon_y = 720;
		float weapon_scale = 0.08f;
		float bang_x = 20.9f, bang_y = -18.7f, bang_z = 78.1f;
		
	};
	AssaultRifleStatus assault_status;

	tnl::Quaternion handrot_;
	tnl::Vector3 handpos_;
	tnl::Quaternion assaultrot_;
	tnl::Vector3 assaultpos_;

	GmCamera* weapon = nullptr;
	dxe::Mesh* BangHandle = nullptr;

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
	//����摜�̈ʒu�Ƒ傫���̕ϐ�
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
	float bang_x = 0, bang_y = 0, bang_z = 0;
	float bang_scalex = 0, bang_scaley = 0;
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