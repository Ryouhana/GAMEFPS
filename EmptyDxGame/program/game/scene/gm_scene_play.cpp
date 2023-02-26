#include "../gm_manager.h"
#include "gm_scene_play.h"
#include "gm_scene_result.h"
#include "gm_scene_gameover.h"
#include "../model/gm_anim_sprite3d.h"



tnl::Quaternion	fix_rot;

ScenePlay::ScenePlay()
{
	player = new Player({ 100, 60, 0 });
	weapon = new Weapon();
	
	
	//zombie->Initialize();
	
}

ScenePlay::~ScenePlay() {
	
		//for (auto itr = zombieList.begin(); itr != zombieList.end();) {
		//	//auto itr = zombieList.begin();
		//	zombieList.erase(itr);
		//}
	
	delete obj_;
}

void ScenePlay::initialzie() {
	GameManager* mgr = GameManager::GetInstance();
	weapon->Initialize();
	
	
	player->hp = 100;
	//weapon->Initialize();

	//�[�[�[�[�[�[BGM�Đ������[�[�[�[�[�[
	//PlaySound1 = LoadSoundMem("sound/escape.mp3");
	PlaySoundMem(PlaySound1, DX_PLAYTYPE_LOOP + DX_PLAYTYPE_BACK);
	

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

	//�[�[�[�[�[�h�[���w�i�̐����[�[�[�[�[�[�[
	Dome_ = dxe::Mesh::CreateSphere(3000);
	Dome_->setTexture(dxe::Texture::CreateFromFile("graphics/yoru_Valo.jpg"));

	//�[�[�[�[�[�[�[���̐����[�[�[�[�[�[�[�[
	Floor_ = dxe::Mesh::CreatePlane({ 6000,6000,0 });
	Floor_->setTexture(dxe::Texture::CreateFromFile("graphics/floor.jpg"));
	Floor_->rot_q_ = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	Floor_->pos_ = { 0, -20, 0 };

	//�[�[�[�[�[�[�؂̃I�u�W�F�N�g�����[�[�[�[�[
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
	GameManager* mgr = GameManager::GetInstance();
	
	player->Update(delta_time);
	weapon->Update(delta_time);
	
	SetMouseDispFlag(FALSE);// �J�[�\���̔�\��
	
	
	

	updateZombies(delta_time);


	tnl::Vector3 hit;

	
	for (int i = 0; i < Popcap; i++) {
		// �[�[�[�[�[�[�[�[�[�[�[�G�l�~�[�̃v���C���[�ǐՁ[�[�[�[�[�[�[�[�[�[�[
	/*	float A = player->GetPostion().x - zombie->pos_zombi.x;
		float B = player->GetPostion().z - zombie->pos_zombi.z;
		float C = sqrt(A * A + B * B);
		zombie->pos_zombi.x += (A / C) * 0.08f;
		zombie->pos_zombi.z += (B / C) * 0.08f;*/

	}
	
	
	//�[�[�[�[�[�[�[�[�[�[�[�[�v���C���[�̎��S�����[�[�[�[�[�[�[�[�[�[�[�[�[
	if (player->hp <= 0) {
		player->hp = 0;
		if (!go_guns) {  //�v���C���[��HP��0�ɂȂ������̉��o�����iSE�Ȃǁj
			StopSoundMem(PlaySound1);
			mgr->ZombieSound = LoadSoundMem("sound/Zombi_SE/eat.mp3");
			PlaySoundMem(mgr->ZombieSound, DX_PLAYTYPE_BACK);
			go_guns = true;
		}
		//�[�[�[�[�[�[HP��0�ɂȂ��Ă��琔�b��ɃV�[���ڍs�܂��J�����̉��o�[�[�[�[�[�[�[
		g_oTime += delta_time;
		player->GetCamera()->c_rot.x -= 0.001f;
		if (g_oTime > 3) {
			mgr->chengeScene(new SceneGameOver());
			g_oTime = 0;
		}
	}


	tnl::Matrix zombi;
	/*if (tnl::IsIntersectLinePlane(camera_->pos_, camera_->pos_ + (ray * 10000.0f), { 10, 10, 10 }, { 0, 1, 0 }, &hit)) {

	}*/



	//�[�[�[�[�[�[�[�[�[�����[�h���Ă�Œ��͑���Ȃ��悤�ɂ��鏈���[�[�[�[�[�[�[
	if (weapon->GunReroad) {
		player->reroadflag = true;
		player->dushFlag = false;
	}
	else player->reroadflag = false;

	//----------------------------------------------------------------
	//�J�[�\���̐���
	//----------------------------------------------------------------
	RECT rcOldClip;
	GetClipCursor(&rcOldClip);

	RECT rcClip;
	GetWindowRect(GetMainWindowHandle(), &rcClip);
	ClipCursor(&rcClip);

	ClipCursor(&rcOldClip);

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->chengeScene(new SceneResult());
		
	}
	
}

void ScenePlay::render()
{
	ZombieSpown(8);
	GameManager* mgr = GameManager::GetInstance();
	player->Render();



	//VECTOR player_pos = VGet(player->GetPostion().x, 0, player->GetPostion().z);
	//MV1SetRotationZYAxis(zombie->ZombieModelHandle, VSub(zombie->vpzombi, player_pos), VGet(0.0f, 1.0f, 0.0f), 0.0f);

	//�J�����ւ̕`�揈��
	obj_->render(player->GetCamera());
	Floor_->render(player->GetCamera());
	Dome_->render(player->GetCamera());
	

	SetFontSize(20); //�����̑傫����ύX
	
	
	//�]���r�̕`�揈��
	for (int i = 0; i < Popcap; i++) {

		zombi_[i]->render(player->GetCamera());

	}

	ChangeFont("�l�r ����");
	
	//DrawOBB(player->GetCamera(), zombie->pos_zombi, zombie->rot_zombi, { zombiBox_x,zombiBox_y,0 });

	SetFontSize(40);
	DrawStringEx(470, 50, RGB(0, 0, 200), "Round %d", round);

	int HPcolor = GetColor(0, 200, 0);
	DrawBox(60, 655, 60 + 200, 655 + 20, HPcolor, FALSE);		//�g��`��
	DrawBox(60, 655, 60 + 200 * player->hp / player->hpMax, 655 + 20, HPcolor, TRUE);	//HP�Q�[�W��`��
	int STcolor = GetColor(200, 150, 0);
	DrawBox(60, 700, 60 + 200, 700 + 20, STcolor, FALSE);		//�g��`��
	DrawBox(60, 700, 60 + 200 * player->stamina / player->staminaMax, 700 + 20, STcolor, TRUE);	//HP�Q�[�W��`��

	DrawRotaGraph(28, 666, 0.040f, 0, HpImage, true);
	DrawRotaGraph(28, 711, 0.17f, 0, StaminaImage, true);
	renderZombies(player->GetCamera());
	weapon->Render();

	DrawStringEx(rei_x, rei_y, -1, "+");


}

void ScenePlay::ZombieSpown(int spowncount) {
	if (!spownFlag) {
		for (int i = 0; i < spowncount; i++) {
			std::shared_ptr<Zombie> zombie = std::make_shared<Zombie>(Zombie());
			zombie->pos_zombi = { 100 * (float)i,0,0 };
			zombiListSmart.push_back(zombie);
		}
		spownFlag = true;
	}
	
}

void ScenePlay::updateZombies(float deltatime) {
	
	auto itr = zombiListSmart.begin();
	while (itr != zombiListSmart.end()) {
		auto zombie = *itr;
		zombie->Update(deltatime,player,weapon);
		
		if (!zombie->isAlive()) {			
			itr = zombiListSmart.erase(itr);
		}
		else {
			++itr;
		}
	}
}

void ScenePlay::renderZombies(GmCamera* player) {
	auto itr = zombiListSmart.begin();
	while (itr != zombiListSmart.end()) {
		auto zombie = *itr;
		zombie->Render(player);
		if (!zombie->isAlive()) {
			itr = zombiListSmart.erase(itr);
		}
		else {
			++itr;
		}
	}
}