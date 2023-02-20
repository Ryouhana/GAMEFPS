#include "gm_scene_base.h"
#include "../model/Player.h"
#include "../model/weapon.h"
#include "../model/Zombie.h"
#include "../model/gm_model.h"

class GmCamera;
class AnimSprite3D;
class ScenePlay : public SceneBase {
public:
	ScenePlay();
	~ScenePlay();
	int Enemynum = 10;
	float c_pos_z = 0;
	float c_x_length = 0;
	float ctrl_x = 1;
	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	Model* obj_ = nullptr;
	Model* obj_1 = nullptr;

	dxe::Mesh* Dome_ = nullptr;
	dxe::Mesh* Floor_ = nullptr;
	dxe::Mesh* Guns_ = nullptr;
	dxe::Mesh* Box_ = nullptr;
	dxe::Mesh* Enemy_ = nullptr;
	int Popcap = 10;
	float obb_x = 20, obb_y = 30;
	AnimSprite3D* zombi_[500] = {};
	Zombie* zombie = nullptr;
	Player* player = nullptr;
	Weapon* weapon = nullptr;


	int box_parts = 0;
	int round = 1;
	int StaminaImage = 0;
	int HpImage = 0;
	int Tama = 0;
	int ModelHandle = 0;

	int PlaySound1 = 0;

	int Walk_SE = 0, Run_SE = 0;



	float g_oTime = 0;
	float g_z = 0;
	float yadd_ = 0;
	float rei_x = 500.0, rei_y = 400.0;
	float floor_x = 0, floor_y = 0;
	float tree_x = 0;
	float enemy_v = 0;
	

	bool go_guns = false;
	bool hitPlayerFlag = false;
	bool shoot_flag = false;
	

	tnl::Vector3 pos_zombi;
	tnl::Quaternion rot_zombi;


};

