#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../gm_camera.h"
#include "Player.h"
#include "../scene/gm_scene_base.h"


class Zombie
{
public:
	

	// ==“G‚ÌSE==
	int Enemy_SE = 0;
	tnl::Vector3 pos_zombi;
	tnl::Quaternion rot_zombi;

	Zombie();
	~Zombie() {};

	void Initialize();
	void Update(float deltaTime);
	void Render(GmCamera* Camera_);
	void Enemy(int ZombieHandle_, int enemyhp);
	void takeDamage(int damage);
	void draw();

	int getModelHandle();
	int getHp();
	bool isAlive();

	int ZombieModelHandle = 0;
	int ZombieHandle = 0;
	int AttachIndex = 0;
	float  TotalTime = 0, PlayTime = 0;
	float zombiBox_x = 40, zombiBox_y = 280;
	DxLib::VECTOR vpzombi;
	MATRIX rotzombi;
private:
	

	int enemyhp_ = 0;
	

	bool isAlive_ = false;
};