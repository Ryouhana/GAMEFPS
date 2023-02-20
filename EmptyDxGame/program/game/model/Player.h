#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../gm_camera.h"


class Player
{
public:
	const int hpMax = 100;
	const int staminaMax = 100;

	int hp = 100;
	int stamina = 100;
	int Walk_SE = 0, Run_SE = 0;
	int HaveWeapon[2] = { 0 };

	Player(tnl::Vector3 pos);
	~Player() {};
	void Initialize(tnl::Vector3 pos);
	void Update(float deltaTime);
	void Render();
	tnl::Vector3 GetPostion();
	GmCamera* GetCamera();
	
private:
	dxe::Mesh* body = nullptr;

	const float dushRecoveryTime = 3;
	const int fieldMax = 1400;

	float walkSpeed = 3;
	float dushSpeed = 5;

	bool dushFlag = false;
	bool jumpFlag = false;
	bool walkFlag = false;

	GmCamera* mainCamera = nullptr;
	tnl::Vector3 moveVelocity;
	tnl::Vector3 moveDirection[4] = { {0, 0, 0},
										{0, 0, 0},
										{0, 0, 0},
										{0, 0, 0} };
	void Move(int i);
	void Dush(int i);
	void Jump();
	void RecoveryStamina(float deltaTime);
	void CameraAngle();
	void HitPoint();

};