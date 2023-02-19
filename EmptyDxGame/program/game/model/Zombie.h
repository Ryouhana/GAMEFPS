#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../gm_camera.h"
#include "Player.h"


class Zombie
{
public:
	const int enemy_hp = 100;
	const float enemy_speed = 8;

	// ==“G‚ÌSE==
	int Enemy_SE = 0;


	Zombie();
	~Zombie() {};

	void Initialize();
	void Update(float deltaTime);
	void Render();
	int ModelHandle = 0;

private:

};