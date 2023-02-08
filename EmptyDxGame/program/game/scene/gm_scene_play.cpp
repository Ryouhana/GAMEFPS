#include "../gm_manager.h"
#include "../gm_camera.h"
#include "gm_scene_play.h"
#include "gm_scene_result.h"
#include "gm_scene_gameover.h"
#include "../model/gm_anim_sprite3d.h"


tnl::Quaternion	fix_rot;

ScenePlay::ScenePlay()
{
	player = new Player({ 100, 60, 0 });
	weapon = new Weapon();
	zombie = new Zombie();
	//zombie->Initialize();
}

ScenePlay::~ScenePlay() {

	delete obj_;
}

void ScenePlay::initialzie() {


	//weapon->Initialize();
	HandGun_Reroad = LoadSoundMem("sound/Gun_SE/HandgunReroad.mp3");
	debug = LoadGraph("graphics/Ring.png");
	//BGM�Đ�����
	//PlaySound1 = LoadSoundMem("sound/escape.mp3");
	PlaySoundMem(PlaySound1, DX_PLAYTYPE_LOOP + DX_PLAYTYPE_BACK);
	//SE�̓ǂݍ���
	Tama_0 = LoadSoundMem("sound/Gun_SE/no.mp3");
	//�摜�̓ǂݍ���

	//Tama = LoadGraph("graphics/tama.png");
	HpImage = LoadGraph("graphics/HP.png");
	StaminaImage = LoadGraph("graphics/stamina.png");

	//player->Initialize({100, 60, 0});

	/*camera_ = new GmCamera();
	camera_->ctrl = GmCamera::CTRL_TYPE_QTN;
	camera_->pos_ = { 100, 60, 0 };
	*/

	for (int i = 0; i < Popcap; i++) {
		zombi_[i] = new AnimSprite3D[](player->GetCamera());
		zombi_[i]->regist(32, 48, "walk_front", "graphics/Zombi_Up.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 48, 0);
		zombi_[i]->regist(32, 48, "walk_back", "graphics/Zombi_Down.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 48, 0);
		zombi_[i]->regist(32, 48, "walk_left", "graphics/Zombi_Left.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 48, 0);
		zombi_[i]->regist(32, 48, "walk_right", "graphics/Zombi_Right.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 48, 0);
		zombi_[i]->setCurrentAnim("walk_front");

		//�]���r�������_���Ő���
		srand(time(0));
		int rand_a = rand() % 2;
		int rand_b = rand() % 2;
		if (rand_b == 0) { rand_b = -1; }
		if (rand_a == 0) { rand_a = -1; }
		zombi_[i]->pos_ = { (float)GetRand((-100 * i) * rand_a),30,(float)GetRand((100 * i) * rand_a) };

	}

	//�h�[���w�i�̐���
	Dome_ = dxe::Mesh::CreateSphere(3000);
	Dome_->setTexture(dxe::Texture::CreateFromFile("graphics/yoru_Valo.jpg"));

	//���̐���
	Floor_ = dxe::Mesh::CreatePlane({ 6000,6000,0 });
	Floor_->setTexture(dxe::Texture::CreateFromFile("graphics/floor.jpg"));
	Floor_->rot_q_ = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	Floor_->pos_ = { 0, -20, 0 };

	//�؂̃I�u�W�F�N�g����
	obj_ = new Model();
	obj_->pos_ = { 0, 0, 500 };
	std::vector<dxe::Mesh*> meshs = dxe::Mesh::CreateFromFileObj("mesh/obj/Tree/Tree.obj");
	obj_->parts_.resize(meshs.size());
	for (int i = 0; i < obj_->parts_.size(); ++i) {
		obj_->parts_[i] = new Parts();
		obj_->parts_[i]->mesh_ = meshs[i];
		obj_->parts_[i]->mesh_->scl_ = { 100.0f, 100.0f, 100.0f };
	}

	/*Player_ = dxe::Mesh::CreateSphereMV(30);
	Player_->setTexture(dxe::Texture::CreateFromFile("graphics/bill.jpg"));
	Player_->pos_ = { 130, 28, 130 };

	stamina = 100;*/


}

void ScenePlay::update(float delta_time)
{
	SetMouseDispFlag(FALSE);// �J�[�\���̔�\��
	GameManager* mgr = GameManager::GetInstance();

	player->Update(delta_time);
	weapon->Update(delta_time);
	zombie->Update(delta_time);
	tnl::Vector3 hit;

	hitPlayerFlag = false;
	for (int i = 0; i < Popcap; i++) {
		// �G�l�~�[�̃v���C���[�ǐ�
		zombi_[i]->pos_;
		float A = player->GetPostion().x - zombi_[i]->pos_.x;
		float B = player->GetPostion().z - zombi_[i]->pos_.z;
		float C = sqrt(A * A + B * B);
		zombi_[i]->pos_.x += (A / C) * 0.5f;
		zombi_[i]->pos_.z += (B / C) * 0.5f;

		/*move.normalize();*/
		int t = tnl::GetXzRegionPointAndOBB(
			player->GetPostion(),
			zombi_[i]->pos_,
			{ obb_x,obb_y,obb_x },
			zombi_[i]->rot_);

		std::string anim_names[4] = {
			"walk_back","walk_right", "walk_front", "walk_left"
		};
		zombi_[i]->setCurrentAnim(anim_names[t]);


	}
	for (int i = 0; i < Popcap; i++) {
		// �]���r�ƃv���C���[�̓����蔻��
		if (tnl::IsIntersectAABB(zombi_[i]->pos_,
			{ obb_x,obb_y,obb_x }, player->GetPostion(), { obb_x,obb_y,obb_x })) {

			hitPlayerFlag = true;
		}

		// �N���X�w�A�ƃ]���r�̓����蔻��
		tnl::Vector3 a_max = tnl::ToMaxAABB(zombi_[i]->pos_, { obb_x,obb_y,obb_x });
		tnl::Vector3 a_min = tnl::ToMinAABB(zombi_[i]->pos_, { obb_x,obb_y,obb_x });
	}


	tnl::Vector3 hitt;
	/*if (tnl::IsIntersectRayOBB(camera_->pos_, (ray * 100000.0f), a_max, a_min, zombi_[i]->rot_.getMatrix(), hitt) && tnl::Input::IsMouseTrigger(tnl::Input::eMouseTrigger::IN_LEFT)) {

	}*/

	//�v���C���[�̎��S����
	if (player->hp <= 0) {
		player->hp = 0;
		if (!go_guns) {
			StopSoundMem(PlaySound1);
			mgr->ZombieSound = LoadSoundMem("sound/Zombi_SE/eat.mp3");
			PlaySoundMem(mgr->ZombieSound, DX_PLAYTYPE_BACK);
			go_guns = true;
		}
		g_oTime += delta_time;
		player->GetCamera()->c_rot.x -= 0.001f;
		if (g_oTime > 10) {
			mgr->chengeScene(new SceneGameOver());
			g_oTime = 0;
			player->hp = 100;
		}
	}

	tnl::Matrix zombi;
	/*if (tnl::IsIntersectLinePlane(camera_->pos_, camera_->pos_ + (ray * 10000.0f), { 10, 10, 10 }, { 0, 1, 0 }, &hit)) {

	}*/

	if (hitPlayerFlag) {
		player->hp -= 2;
	}
	if (shoot_flag) {
		if (tnl::Input::IsMouseTrigger(tnl::Input::eMouseTrigger::IN_LEFT)) {
			player->hp -= 10;
		}
	}


	if (tnl::Input::IsMouseTrigger(tnl::Input::eMouseTrigger::IN_LEFT) && !GunReroad) {
		if (weapon->ammoClip > 0) {
			PlaySoundMem(mgr->juusei, DX_PLAYTYPE_BACK);

			weapon->ammoClip--;
		}

		if (weapon->ammoClip <= 0) {
			weapon->ammoClip = 0;
			PlaySoundMem(Tama_0, DX_PLAYTYPE_BACK);
		}
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_R)) {
		amountNeed = weapon->maxAmmoClip - weapon->ammoClip;
		//�}�K�W���ɕ�[����ׂ��e�򐔂�菊�����Ă�e�򐔂��傫����
		ammoAvailable = amountNeed < weapon->ammunition ? amountNeed : weapon->ammunition;
		if (amountNeed != 0 && weapon->ammunition != 0) {
			if (!GunReroad)PlaySoundMem(HandGun_Reroad, DX_PLAYTYPE_BACK);
			GunReroad = true;
		}


	}
	if (GunReroad) {
		debug_i += 2.0f;

		if (debug_i >= 100) {
			weapon->ammunition -= ammoAvailable;
			weapon->ammoClip += ammoAvailable;
			debug_i = 0;
			GunReroad = false;
		}
	}
	//----------------------------------------------------------------
	//�J�[�\���̐���
	//----------------------------------------------------------------
	RECT rcOldClip;
	GetClipCursor(&rcOldClip);

	RECT rcClip;
	GetWindowRect(GetMainWindowHandle() + 100, &rcClip);
	ClipCursor(&rcClip);

	ClipCursor(&rcOldClip);

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->chengeScene(new SceneResult());
	}



}

void ScenePlay::render()
{

	player->Render();
	//�J�����ւ̕`�揈��
	obj_->render(player->GetCamera());
	Floor_->render(player->GetCamera());
	Dome_->render(player->GetCamera());


	SetFontSize(20); //�����̑傫����ύX
	zombie->Render();
	//�]���r�̕`�揈��
	for (int i = 0; i < Popcap; i++) {

		zombi_[i]->render(player->GetCamera());


	}

	ChangeFont("�l�r ����");
	DrawStringEx(rei_x, rei_y, -1, "+");


	SetFontSize(40);
	DrawStringEx(470, 50, RGB(0, 0, 200), "Round %d", round);

	int HPcolor = GetColor(0, 200, 0);
	DrawBox(60, 655, 60 + 200, 655 + 20, HPcolor, FALSE);		//�g��`��
	DrawBox(60, 655, 60 + 200 * player->hp / player->hpMax, 655 + 20, HPcolor, TRUE);	//HP�Q�[�W��`��
	int STcolor = GetColor(200, 150, 0);
	DrawBox(60, 700, 60 + 200, 700 + 20, STcolor, FALSE);		//�g��`��
	DrawBox(60, 700, 60 + 200 * player->stamina / player->staminaMax, 700 + 20, STcolor, TRUE);	//HP�Q�[�W��`��

	DrawCircleGauge(rei_x + 5, rei_y + 8.5f, debug_i, debug, 0.0f, 0.08f);




	DrawRotaGraph(28, 666, 0.040f, 0, HpImage, true);
	DrawRotaGraph(28, 711, 0.17f, 0, StaminaImage, true);
	weapon->Render();
	

}