#include "Zombie.h"
#include "DxLib.h"

using namespace std;

Zombie::Zombie() {
	 ZombieModelHandle = MV1LoadModel("zombietaro/zombie.pmx");
	 // ３Ｄモデルの1番目のアニメーションをアタッチする
	

	 pos_zombi.y = -20.f;
	Enemy(ZombieModelHandle, 100);
}

void Zombie::Initialize() {


}

void Zombie::Update(float deltaTime, Player* player, Weapon* weapon) {
	//武器による敵へのダメージ処理
//------------------------------------------------------------------------------------------
	WeaponDamage(player, weapon);
	//プレイヤーに向かって近づいてくる関数
	ZombieMove(player);
	
	//ーーーーーーープレイヤーと敵が接触した時のhp減少フラグーーーーーーーーー
	Playerdamage(player);
	
	ZombieDead(deltaTime);
	//ZombieMove(player);

	
	
	
	// 銃でゾンビを撃つ処理
		// アタッチしたアニメーションの総再生時間を取得する
	TotalTime = MV1GetAttachAnimTotalTime(ZombieHandle, AttachIndex);

	if (!isAlive()) {
		MV1DeleteModel(getModelHandle());
	}
	if (enemyhp_ > 0) {
		// 再生時間を進める
		PlayTime += 1.0f;
	}
	
	if (PlayTime >= TotalTime && enemyhp_ > 0) {
		//PlayTime = TotalTime;
		PlayTime = 0.0f;
	}
	
	//MV1DeleteModel(ZombieModelHandle);
}

void Zombie::Render(GmCamera* Camera_) {
	Camera_->update();
	MATRIX view, proj;
	memcpy(view.m, Camera_->view_.m, sizeof(float) * 16);
	memcpy(proj.m, Camera_->proj_.m, sizeof(float) * 16);
	SetCameraViewMatrix(view);
	SetupCamera_ProjectionMatrix(proj);
	
	vpzombi = VGet(pos_zombi.x, pos_zombi.y, pos_zombi.z);

	//rot_(tnl::Quaternion型)をMATRIX型に変換
	
	memcpy(rotzombi.m, rot_zombi.getMatrix().m, sizeof(float) * 16);
	MV1SetRotationMatrix(ZombieHandle, rotzombi);
	MV1SetScale(ZombieHandle, { 5.0f,5.0f,5.0f });
	MV1SetPosition(ZombieHandle, vpzombi);

	// 再生時間をセットする
	MV1SetAttachAnimTime(ZombieHandle, AttachIndex, PlayTime);
	for (int i = 0; i < 100; i++) {
		MV1SetMaterialOutLineWidth(ZombieHandle, i, 0);
	}
	if (isAlive_) {
		MV1DrawModel(ZombieHandle);
		
	}

}

void Zombie::Enemy(int ZombieHandle_, int enemyhp) {
	zombie_opecity = 1.0f;
	ZombieHandle = ZombieHandle_;
	AttachAnimation(Walk_0);
	enemyhp_ = enemyhp;
	isAlive_ = true;

}


void Zombie::AttachAnimation(int animetype) {
	if (!animationroadFlag) {
		MV1DetachAnim(ZombieHandle, AttachIndex);
		animationtype = animetype;

		PlayTime = 0;
		int test = 0;
		test = -1;
		AttachIndex = MV1AttachAnim(ZombieHandle, animationtype, test);
		animationroadFlag = true;
	}
	animationroadFlag = false;
}

void Zombie::takeDamage(int damage) {
	if (enemyhp_ > 0) {
		enemyhp_ -= damage;
	}
	
	if (enemyhp_ <= 0 && !deadFlag) {
		srand(time(0));
		int randdown = 0;
		int deadrand = rand() % 2 + 1;
		if (deadrand == 1) {
			randdown = Down_back;
		}
		if (deadrand == 2) {
			randdown = Down_center;
		}
		AttachAnimation(randdown);
		deadFlag = true;
	}

	
}

void Zombie::ZombieDead(float delta_time) {
	
	//dead_count += delta_time;
	if (enemyhp_ <= 0) {
	
		
		PlayTime += 1;
		if (PlayTime >= TotalTime) {
			PlayTime = TotalTime;
			
		}
		if (PlayTime == TotalTime)
			MV1SetOpacityRate(ZombieHandle, zombie_opecity);
			zombie_opecity -= 0.01f;
		
		if (zombie_opecity <= 0) {
			isAlive_ = false;
		}
		
		
	}
}


void Zombie::WeaponDamage(Player* player, Weapon* weapon) {
	
	if (weapon->ammoClip != 0) {
		tnl::Vector3 a_max = tnl::ToMaxAABB(pos_zombi, { zombiBox_x,zombiBox_y, zombiBox_x });
		tnl::Vector3 a_min = tnl::ToMinAABB(pos_zombi, { zombiBox_x,zombiBox_y, zombiBox_x });
		tnl::Vector3 hitt;
		if (weapon->mousewheel == weapon->HandGun) {
			

				if (tnl::IsIntersectRayOBB(player->GetPostion(), (player->ray * 100000.0f), a_max, a_min, rot_zombi.getMatrix(), hitt) && tnl::Input::IsMouseTrigger(tnl::Input::eMouseTrigger::IN_LEFT) && !weapon->GunReroad && weapon->shoottime == 0) {
					// 銃弾が当たったと仮定して、ゾンビにダメージを与える

					takeDamage(10);


				}


			
			
		}
		if (weapon->mousewheel == weapon->AssaultRifle) {
			if (tnl::IsIntersectRayOBB(player->GetPostion(), (player->ray * 100000.0f), a_max, a_min, rot_zombi.getMatrix(), hitt) && tnl::Input::IsMouseDown(tnl::Input::eMouse::LEFT) && !weapon->GunReroad && weapon->shoottime == 0 && !hit) {
				// 銃弾が当たったと仮定して、ゾンビにダメージを与える
			
					takeDamage(20);
				
			}
		}
		if (weapon->mousewheel == weapon->SubMachineGun) {
			if (tnl::IsIntersectRayOBB(player->GetPostion(), (player->ray * 100000.0f), a_max, a_min, rot_zombi.getMatrix(), hitt) && tnl::Input::IsMouseDown(tnl::Input::eMouse::LEFT) && !weapon->GunReroad && weapon->shoottime == 0) {
				// 銃弾が当たったと仮定して、ゾンビにダメージを与える
				takeDamage(15);
			}
		}
	}
}

void Zombie::ZombieMove(Player* player) {
	// ーーーーーーーーーーーエネミーのプレイヤー追跡ーーーーーーーーーーー
	float A = player->GetPostion().x - pos_zombi.x;
	float B = player->GetPostion().z - pos_zombi.z;
	float C = sqrt(A * A + B * B);
	pos_zombi.x += (A / C) * 0.2f;
	pos_zombi.z += (B / C) * 0.2f;
}

void Zombie::draw(){
	
}

void Zombie::Playerdamage(Player* player) {
	if (isAlive()) {
		// ーーーーーーーーーーーーーーゾンビとプレイヤーの当たり判定ーーーーーーーーーー
		if (tnl::IsIntersectAABB(pos_zombi,
			{ zombiBox_x,zombiBox_y,zombiBox_x }, player->GetPostion(), { zombiBox_x,zombiBox_y,zombiBox_x })) {
			if (!hitPlayerFlag) {
				player->hp -= 2;
				hitPlayerFlag = true;
			}
			hitPlayerFlag = false;
		}

	}
}


// ゲッター
int Zombie::getModelHandle(){
	return ZombieHandle;
}

int Zombie::getHp(){
	return enemyhp_;
}

bool Zombie::isAlive(){
	return isAlive_;
}