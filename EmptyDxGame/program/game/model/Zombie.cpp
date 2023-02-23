#include "Zombie.h"
#include "../model/Player.h"
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

void Zombie::Update(float deltaTime) {
	
	// 銃でゾンビを撃つ処理
		// アタッチしたアニメーションの総再生時間を取得する
	TotalTime = MV1GetAttachAnimTotalTime(ZombieHandle, AttachIndex);

	if (!isAlive()) {
		MV1DeleteModel(getModelHandle());
	}
	// 再生時間を進める
	PlayTime += 1;
	if (PlayTime >= TotalTime) {
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
	ZombieHandle = ZombieHandle_;
	AttachIndex = MV1AttachAnim(ZombieHandle_, 0, -1);
	enemyhp_ = enemyhp;
	isAlive_ = true;

}

void Zombie::takeDamage(int damage) {
	enemyhp_ -= damage;
	if (enemyhp_ <= 0) {
		isAlive_ = false;
	}
}

void Zombie::draw(){
	
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