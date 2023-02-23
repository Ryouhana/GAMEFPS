#include "weapon.h"
#include "../gm_manager.h"
#include "../model/Player.h"
#include "Effect.h"
#include "DxLib.h"

using namespace std;

Weapon::Weapon() {
	hand_status.HandGunModelHandle = MV1LoadModel("MEUPistol/MEUPistol.pmd");
	hand_status.HandGunImage = LoadGraph("graphics/Handgun.png");
	sub_status.SubMachineGunImage = LoadGraph("graphics/MP5.png");
	assault_status.AssaultRifleImage = LoadGraph("graphics/XM177.png");
	
	assault_status.AssaultModelHandle = MV1LoadModel("XM177/Xm177.pmx");
	Tama_0 = LoadSoundMem("sound/Gun_SE/no.mp3");
	HandGun_Reroad = LoadSoundMem("sound/Gun_SE/HandgunReroad.mp3");
	debug = LoadGraph("graphics/Ring.png");

	//撃った際の火花の画像
	BangHandle = dxe::Mesh::CreatePlane({ 50, 50, 0 });
	BangHandle ->setTexture(dxe::Texture::CreateFromFile("graphics/bang.png"));
//	BangHandle ->rot_q_ = tnl::Quaternion::RotationAxis({ 0, 0, 0 }, tnl::ToRadian(90));
	
	weapon = new GmCamera;
	
}
void Weapon::Initialize() {
	
	//ーーーーーーーー各武器の所持弾薬とマガジン内の弾薬のステータスを仮の変数に一度だけ代入ーーーーーーー
	demo_assaultammoClip = assault_status.ammoClip;
	demo_assaultammunition = assault_status.ammunition;
	demo_subammoClip = sub_status.ammoClip;
	demo_subammunition = sub_status.ammunition;
	demo_handammoClip = hand_status.ammoClip;
	demo_handammunition = hand_status.ammunition;

	

}

void Weapon::Update(float deltaTime) {
	
	GameManager* mgr = GameManager::GetInstance();
	/*SetLightEnable(FALSE);*/
	int wheelMax = 3;
	int wheelMin = 1;
	if (!GunReroad) {
		mousewheel += GetMouseWheelRotVol();
	}
	
	if (mousewheel > wheelMax) {
		mousewheel = 1;
	}
	if (mousewheel < wheelMin) {
		mousewheel = 3;
	}
	//ーーーーーーーーサブマシンガンを持ってる時の処理ーーーーーーーーーー
	if (mousewheel == SubMachineGun) {
		if (!SubMachineGunFlah) {
			reroadtime = sub_status.reroadtime;
			ammunition = demo_subammunition;
			maxAmmunition = sub_status.maxAmmunition;
			ammoClip = demo_subammoClip;
			maxAmmoClip = sub_status.maxAmmoClip;
			amountNeed = sub_status.amountNeed;
			ammoAvailable = sub_status.ammoAvailable;
			SubMachineGunFlah = true;
		}
		SwitchWeapon(SubMachineGun);
	}
	else {
		SubMachineGunFlah = false;
		
	}
	//ーーーーーーーーーアサルトライフルを持ってる時の処理ーーーーーーーー
	if (mousewheel == AssaultRifle) {
		if (!AssaultRifleFlag) {
			reroadtime = assault_status.reroadtime;
			ammunition = demo_assaultammunition;
			maxAmmunition = assault_status.maxAmmunition;
			ammoClip = demo_assaultammoClip;
			maxAmmoClip = assault_status.maxAmmoClip;
			amountNeed = assault_status.amountNeed;
			ammoAvailable = assault_status.ammoAvailable;
			AssaultRifleFlag = true;
		}
		
			SwitchWeapon(AssaultRifle);
	}
	else {
		AssaultRifleFlag = false;
	}
	//ーーーーーーーーハンドガンを持ってる時の処理ーーーーーーーーーーー
	if (mousewheel == HandGun) {
		if (!HandGunFlag ) {
			
			reroadtime = hand_status.reroadtime;
			ammunition = demo_handammunition;
			maxAmmunition = hand_status.maxAmmunition;
			ammoClip = demo_handammoClip;
			maxAmmoClip = hand_status.maxAmmoClip;
			amountNeed = hand_status.amountNeed;
			ammoAvailable = hand_status.ammoAvailable;
			HandGunFlag = true;
		}

		SwitchWeapon(HandGun);
	}
	else {
		HandGunFlag = false;
		
	}
	//ーーーーーーーーー武器のリロード処理ーーーーーーーーーー
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_R)) {

		amountNeed = maxAmmoClip - ammoClip;
		//マガジンに補充するべき弾薬数より所持してる弾薬数が大きいか
		ammoAvailable = amountNeed < ammunition ? amountNeed : ammunition;

		if (amountNeed != 0 && ammunition != 0) {
			if (!GunReroad)PlaySoundMem(HandGun_Reroad, DX_PLAYTYPE_BACK);
			GunReroad = true;

		}
	}
	//ーーーーーーーーーリロード中の演出ーーーーーーー
	if (GunReroad) {
		normalreroad_time += reroadtime;

		if (normalreroad_time >= 100) {
			ammunition -= ammoAvailable;
			ammoClip += ammoAvailable;
			//武器を切り替えてもリロード後の弾数になる
			if (mousewheel == AssaultRifle) {
				demo_assaultammoClip = ammoClip;
				demo_assaultammunition = ammunition;
			}
			if (mousewheel == SubMachineGun) {
				demo_subammoClip = ammoClip;
				demo_subammunition = ammunition;
			}
			if (mousewheel == HandGun) {
				demo_handammoClip = ammoClip;
				demo_handammunition = ammunition;
			}
			normalreroad_time = 0;
			GunReroad = false;
		}

	}
	// ３Ｄモデルの描画
	if (tnl::Input::IsKeyDown(eKeys::KB_UP)) {
		BangHandle->pos_.y -= 1.1f;
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_DOWN)) {
		BangHandle->pos_.y += 1.1f;
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_LEFT)) {
		BangHandle->pos_.x -= 1.1f;
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) {
		BangHandle->pos_.x += 1.1f;
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_Q)) {
		BangHandle->pos_.z -= 1.1f;
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_E)) {
		BangHandle->pos_.z += 1.1f;
	}
	
	if (tnl::Input::IsKeyDown(eKeys::KB_Z)) {
		bang_scaley += 1.0f;

	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_X)) {
		bang_scalex += 1.0f;
	}

	if (BangHandle->scl_.x >= 100.f) {
		BangHandle->scl_.x = 0;
	}
	if (BangHandle->scl_.y >= 100.f) {
		BangHandle->scl_.y = 0;
	}

		
		
}

void Weapon::Render() {
	weapon->update();

	

	SetFontSize(55);
	//文字の描画
	//if (HandGunFlag) {
		DrawStringEx(840, 680, -1, "%2d", ammoClip);
		SetFontSize(40);
		DrawStringEx(895, 720, -1, "/%d", ammunition);

		DrawRotaGraph(weapon_x, weapon_y, weapon_scale, 0, NormalWeaponImage, true);
		DrawCircleGauge(reroad_x + 5, reroad_y + 8.5f, normalreroad_time, debug, 0.0f, 0.09f);
	//}
	DrawStringEx(840, 600, -1, "%d", mousewheel);
	
	

	MATRIX view, proj;
	memcpy(view.m, weapon->view_.m, sizeof(float) * 16);
	memcpy(proj.m, weapon->proj_.m, sizeof(float) * 16);
	SetCameraViewMatrix(view);
	SetupCamera_ProjectionMatrix(proj);

	DxLib::VECTOR handvp;
	handvp = VGet(handpos_.x, handpos_.y, handpos_.z);
	//rot_(tnl::Quaternion型)をMATRIX型に変換
	MATRIX handrot;
	memcpy(handrot.m, handrot_.getMatrix().m, sizeof(float) * 16);

	DxLib::VECTOR assaultvp;
	assaultvp = VGet(assaultpos_.x, assaultpos_.y, assaultpos_.z);
	//rot_(tnl::Quaternion型)をMATRIX型に変換
	MATRIX assaultrot;
	memcpy(assaultrot.m, assaultrot_.getMatrix().m, sizeof(float) * 16);
	for (int i = 0; i < 100; i++) {
		MV1SetMaterialOutLineWidth(assault_status.AssaultModelHandle, i, 0);
		MV1SetMaterialOutLineWidth(hand_status.HandGunModelHandle, i, 0);
	}

	MV1SetRotationMatrix(assault_status.AssaultModelHandle, assaultrot);
	MV1SetScale(assault_status.AssaultModelHandle, { 1.0f,1.0f,1.0f });
	MV1SetPosition(assault_status.AssaultModelHandle, assaultvp);

	MV1SetRotationMatrix(hand_status.HandGunModelHandle, handrot);
	MV1SetScale(hand_status.HandGunModelHandle, { 1.0f,1.0f,1.0f });
	MV1SetPosition(hand_status.HandGunModelHandle, handvp);

	
	if (mousewheel == AssaultRifle) {
		if (!GunReroad && shoottime == 0 && ammoClip > 0) {
			BangHandle->render(weapon);
		}
	}
	if (mousewheel == HandGun) {
		if (!GunReroad && shoottime == 0 && ammoClip > 0) {
			BangHandle->render(weapon);
		}
	}
	
	
	DrawFormatString(0, 0, GetColor(255, 255, 255), "x=%.1f y=%.1f z=%.1f", BangHandle->pos_.x, BangHandle->pos_.y, BangHandle->pos_.z);
	DrawFormatString(0, 200, GetColor(255, 255, 255), "x=%.1f y=%.1f", bang_scalex, bang_scaley);
	
}

//ーーーーーーーーー武器を切り替えた後のそれぞれの処理を実行する関数ーーーーーーーーーーー
void Weapon::SwitchWeapon(WeaponType weapontype) {

	GameManager* mgr = GameManager::GetInstance();
	switch (weapontype) {
	case WeaponType::AssaultRifle:
		if (!GunReroad) {
			MV1DrawModel(assault_status.AssaultModelHandle);
		}
		BangHandle->pos_ = { bang_x, bang_y, bang_z };
		assaultrot_ = tnl::Quaternion::RotationAxis({ 0,1,0 }, tnl::ToRadian(180));
		assaultpos_.x = 1.1f, assaultpos_.y = -2.2f, assaultpos_.z = -97.9f;
		NormalWeaponImage = assault_status.AssaultRifleImage;
		NormalWeapon_Reroad = assault_status.AssaultRifle_Reroad;
		reroad_x = assault_status.reroad_x;
		reroad_y = assault_status.reroad_y;
		//アサルトライフルの画像位置と大きさを代入
		weapon_x = assault_status.weapon_x;
		weapon_y = assault_status.weapon_y;
		weapon_scale = assault_status.weapon_scale;
		bang_x = assault_status.bang_x;
		bang_y = assault_status.bang_y;
		bang_z = assault_status.bang_z;
		shoottime++;
		
		if (tnl::Input::IsMouseDown(tnl::Input::eMouse::LEFT) && !GunReroad && shoottime >= assault_status.shoottime) {

			if (ammoClip > 0) {
				PlaySoundMem(mgr->juusei, DX_PLAYTYPE_BACK);
			
				ammoClip--;
				if (mousewheel == AssaultRifle) {
					demo_assaultammoClip = ammoClip;
				}
			}

			if (ammoClip <= 0) {
				ammoClip = 0;
				PlaySoundMem(Tama_0, DX_PLAYTYPE_BACK);
				
			}
			shoottime = 0;
		}
		break;
	case WeaponType::HandGun:
		
		if (!GunReroad) {
			MV1DrawModel(hand_status.HandGunModelHandle);
		}
		BangHandle->pos_ = { bang_x, bang_y, bang_z };
		handrot_ = tnl::Quaternion::RotationAxis({ 0,1,0 }, tnl::ToRadian(180));
		handpos_.x = 1.2f, handpos_.y = -1.2f, handpos_.z = -96.6f;
		NormalWeaponImage = hand_status.HandGunImage;
		NormalWeapon_Reroad = hand_status.HandGun_Reroad;
		reroad_x = hand_status.reroad_x;
		reroad_y = hand_status.reroad_y;
		//ハンドガンの画像位置と大きさを代入
		weapon_x = hand_status.weapon_x;
		weapon_y = hand_status.weapon_y;
		weapon_scale = hand_status.weapon_scale;
		bang_x = hand_status.bang_x;
		bang_y = hand_status.bang_y;
		bang_z = hand_status.bang_z;
		shoottime++;
		if (tnl::Input::IsMouseTrigger(tnl::Input::eMouseTrigger::IN_LEFT) && !GunReroad && shoottime >= hand_status.shoottime) {
			
			if (ammoClip > 0 && ammoClip != 0) {
				PlaySoundMem(mgr->juusei, DX_PLAYTYPE_BACK);

				ammoClip--;
				if (mousewheel == HandGun) {
					demo_handammoClip = ammoClip;
				}
			}
			if (ammoClip <= 0) {
				
					
				PlaySoundMem(Tama_0, DX_PLAYTYPE_BACK);
				ammoClip = 0;
				

			}
			
			
			shoottime = 0;
		}
		break;
	case WeaponType::SubMachineGun:
		BangHandle->pos_ = { bang_x, bang_y, bang_z };
		NormalWeaponImage = sub_status.SubMachineGunImage;
		NormalWeapon_Reroad = sub_status.SubMachinGun_Rrroad;
		reroad_x = sub_status.reroad_x;
		reroad_y = sub_status.reroad_y;
		//サブマシンガンの画像位置と大きさを代入
		weapon_x = sub_status.weapon_x;
		weapon_y = sub_status.weapon_y;
		weapon_scale = sub_status.weapon_scale;
		shoottime++;
		if (tnl::Input::IsMouseDown(tnl::Input::eMouse::LEFT) && !GunReroad && shoottime >= sub_status.shoottime) {

			if (ammoClip > 0) {
				PlaySoundMem(mgr->juusei, DX_PLAYTYPE_BACK);

				ammoClip--;
				if (mousewheel == SubMachineGun) {
					demo_subammoClip = ammoClip;
				}

			}

			if (ammoClip <= 0) {
				ammoClip = 0;
				PlaySoundMem(Tama_0, DX_PLAYTYPE_BACK);
			}
			shoottime = 0;
		}
		break;
	default:
		return;

	 }
}


