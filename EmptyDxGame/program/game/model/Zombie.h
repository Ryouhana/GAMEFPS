#pragma once
#include "../gm_camera.h"
#include "Player.h"
#include "../model/weapon.h"
#include "../scene/gm_scene_base.h"


class Zombie
{
public:
	enum Animationtype {
		Attack,
		Down_back,
		Walk_0,
		Walk_1,
		Walk_2,
		Down_center

	};
	

	// ==“G‚ÌSE==
	int Enemy_SE = 0;
	tnl::Vector3 pos_zombi;
	tnl::Quaternion rot_zombi;

	Zombie();
	~Zombie() { 
		
	
	};

	void Initialize();
	void Update(float deltaTimer, Player* player, Weapon* weapon);
	void Render(GmCamera* Camera_);
	void Enemy(int ZombieHandle_, int enemyhp);
	void takeDamage(int damage);
	void draw();
	void AttachAnimation(int animetype);
	void ZombieDead(float delta_time);
	void WeaponDamage(Player* player, Weapon* weapon);
	void Playerdamage(Player* player);
	void ZombieMove(Player* player);
	int getModelHandle();
	int getHp();

	bool isAlive();
	bool animationroadFlag = false;
	bool hitPlayerFlag = false;
	bool deadFlag = false;
	bool hit = false;
	int ZombieModelHandle = 0;
	int ZombieHandle = 0;
	int AttachIndex = 0;
	int animationtype = 0;
	float  TotalTime = 0, PlayTime = 0;
	float zombiBox_x = 40, zombiBox_y = 280;
	float zombie_opecity = 0;
	DxLib::VECTOR vpzombi;
	MATRIX rotzombi;
private:
	

	int enemyhp_ = 0;
	

	bool isAlive_ = false;
};