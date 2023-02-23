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
	zombie = new Zombie();
	
	//zombie->Initialize();
	
}

ScenePlay::~ScenePlay() {

	delete obj_;
}

void ScenePlay::initialzie() {
	
	weapon->Initialize();
	

	player->hp = 100;
	//weapon->Initialize();

	//ーーーーーーBGM再生処理ーーーーーー
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

		//ゾンビをランダムで生成
		srand(time(0));
		int rand_a = rand() % 2;
		int rand_b = rand() % 2;
		if (rand_b == 0) { rand_b = -1; }
		if (rand_a == 0) { rand_a = -1; }
		zombi_[i]->pos_ = { (float)GetRand((-100 * i) * rand_a),30,(float)GetRand((100 * i) * rand_a) };

	}

	//ーーーーードーム背景の生成ーーーーーーー
	Dome_ = dxe::Mesh::CreateSphere(3000);
	Dome_->setTexture(dxe::Texture::CreateFromFile("graphics/yoru_Valo.jpg"));

	//ーーーーーーー床の生成ーーーーーーーー
	Floor_ = dxe::Mesh::CreatePlane({ 6000,6000,0 });
	Floor_->setTexture(dxe::Texture::CreateFromFile("graphics/floor.jpg"));
	Floor_->rot_q_ = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	Floor_->pos_ = { 0, -20, 0 };

	//ーーーーーー木のオブジェクト生成ーーーーー
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
	
	player->Update(delta_time);
	weapon->Update(delta_time);
	zombie->Update(delta_time);
	SetMouseDispFlag(FALSE);// カーソルの非表示
	GameManager* mgr = GameManager::GetInstance();


	tnl::Vector3 hit;

	hitPlayerFlag = false;
	for (int i = 0; i < Popcap; i++) {
		// ーーーーーーーーーーーエネミーのプレイヤー追跡ーーーーーーーーーーー
		zombie->pos_zombi;
		float A = player->GetPostion().x - zombie->pos_zombi.x;
		float B = player->GetPostion().z - zombie->pos_zombi.z;
		float C = sqrt(A * A + B * B);
		zombie->pos_zombi.x += (A / C) * 0.08f;
		zombie->pos_zombi.z += (B / C) * 0.08f;

	}
	if (zombie->isAlive()) {
		// ーーーーーーーーーーーーーーゾンビとプレイヤーの当たり判定ーーーーーーーーーー
		if (tnl::IsIntersectAABB(zombie->pos_zombi,
			{ zombiBox_x,zombiBox_y,zombiBox_x }, player->GetPostion(), { zombiBox_x,zombiBox_y,zombiBox_x })) {

			hitPlayerFlag = true;
		}
	}
		
	

	// // ーーーーーーーーーーークロスヘアとゾンビの当たり判定ーーーーーーーーーーーーー
	//tnl::Vector3 a_max = tnl::ToMaxAABB(zombie->pos_zombi, { zombiBox_x,zombiBox_y, zombiBox_x });
	//tnl::Vector3 a_min = tnl::ToMinAABB(zombie->pos_zombi, { zombiBox_x,zombiBox_y, zombiBox_x });
	//tnl::Vector3 hitt;
	//if (weapon->mousewheel == weapon->HandGun) {
	//	if (tnl::IsIntersectRayOBB(player->GetPostion(), (player->ray * 100000.0f), a_max, a_min, zombie->rot_zombi.getMatrix(), hitt) && tnl::Input::IsMouseTrigger(tnl::Input::eMouseTrigger::IN_LEFT)) {
	//		// 銃弾が当たったと仮定して、ゾンビにダメージを与える
	//		zombie->takeDamage(10);
	//	}

	//}
	//if (weapon->mousewheel == weapon->AssaultRifle) {
	//	if (tnl::IsIntersectRayOBB(player->GetPostion(), (player->ray * 100000.0f), a_max, a_min, zombie->rot_zombi.getMatrix(), hitt) && tnl::Input::IsMouseTrigger(tnl::Input::eMouseTrigger::IN_LEFT) && weapon->shoottime) {
	//		// 銃弾が当たったと仮定して、ゾンビにダメージを与える
	//		zombie->takeDamage(20);
	//	}
	//}
	//if (weapon->mousewheel == weapon->SubMachineGun) {
	//	if (tnl::IsIntersectRayOBB(player->GetPostion(), (player->ray * 100000.0f), a_max, a_min, zombie->rot_zombi.getMatrix(), hitt) && tnl::Input::IsMouseTrigger(tnl::Input::eMouseTrigger::IN_LEFT)) {
	//		// 銃弾が当たったと仮定して、ゾンビにダメージを与える
	//		zombie->takeDamage(15);
	//	}
	//}

	mgr->WeaponDamage(player, zombie, weapon);


	//ーーーーーーーーーーーープレイヤーの死亡処理ーーーーーーーーーーーーー
	if (player->hp <= 0) {
		player->hp = 0;
		if (!go_guns) {  //プレイヤーのHPが0になった時の演出処理（SEなど）
			StopSoundMem(PlaySound1);
			mgr->ZombieSound = LoadSoundMem("sound/Zombi_SE/eat.mp3");
			PlaySoundMem(mgr->ZombieSound, DX_PLAYTYPE_BACK);
			go_guns = true;
		}
		//ーーーーーーHPが0になってから数秒後にシーン移行またカメラの演出ーーーーーーー
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

	//ーーーーーーープレイヤーと敵が接触した時のhp減少フラグーーーーーーーーー
	if (hitPlayerFlag) {
		player->hp -= 2;
	}

	//ーーーーーーーーーリロードしてる最中は走れないようにする処理ーーーーーーー
	if (weapon->GunReroad) {
		player->reroadflag = true;
		player->dushFlag = false;
	}
	else player->reroadflag = false;

	//----------------------------------------------------------------
	//カーソルの制御
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
	player->Render();

	zombie->Render(player->GetCamera());

	VECTOR player_pos = VGet(player->GetPostion().x, 0, player->GetPostion().z);
	MV1SetRotationZYAxis(zombie->ZombieModelHandle, VSub(zombie->vpzombi, player_pos), VGet(0.0f, 1.0f, 0.0f), 0.0f);

	//カメラへの描画処理
	obj_->render(player->GetCamera());
	Floor_->render(player->GetCamera());
	Dome_->render(player->GetCamera());
	

	SetFontSize(20); //文字の大きさを変更
	
	
	//ゾンビの描画処理
	for (int i = 0; i < Popcap; i++) {

		zombi_[i]->render(player->GetCamera());

	}

	ChangeFont("ＭＳ 明朝");
	
	DrawOBB(player->GetCamera(), zombie->pos_zombi, zombie->rot_zombi, { zombiBox_x,zombiBox_y,0 });

	SetFontSize(40);
	DrawStringEx(470, 50, RGB(0, 0, 200), "Round %d", round);

	int HPcolor = GetColor(0, 200, 0);
	DrawBox(60, 655, 60 + 200, 655 + 20, HPcolor, FALSE);		//枠を描画
	DrawBox(60, 655, 60 + 200 * player->hp / player->hpMax, 655 + 20, HPcolor, TRUE);	//HPゲージを描画
	int STcolor = GetColor(200, 150, 0);
	DrawBox(60, 700, 60 + 200, 700 + 20, STcolor, FALSE);		//枠を描画
	DrawBox(60, 700, 60 + 200 * player->stamina / player->staminaMax, 700 + 20, STcolor, TRUE);	//HPゲージを描画

	DrawRotaGraph(28, 666, 0.040f, 0, HpImage, true);
	DrawRotaGraph(28, 711, 0.17f, 0, StaminaImage, true);
	
	weapon->Render();

	DrawStringEx(rei_x, rei_y, -1, "+");


}
