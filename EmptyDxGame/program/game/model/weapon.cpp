#include "weapon.h"
#include "../gm_manager.h"
#include "../scene/gm_scene_play.h"
using namespace std;

Weapon::Weapon() {
	hand_status.HandGunImage = LoadGraph("graphics/Handgun.png");
	sub_status.SubMachineGunImage = LoadGraph("graphics/MP5.png");
	assault_status.AssaultRifleImage = LoadGraph("graphics/XM177.png");
	/*hand_status.HandGunModelHandle = MV1LoadModel("MEUPistol/MEUPistol.pmd");
	assault_status.AssaultModelHandle = MV1LoadModel("XM177/Xm177.pmx");*/
	Tama_0 = LoadSoundMem("sound/Gun_SE/no.mp3");
	HandGun_Reroad = LoadSoundMem("sound/Gun_SE/HandgunReroad.mp3");
	debug = LoadGraph("graphics/Ring.png");
	//player_ = new Player({ 100, 60, 0 });
}
void Weapon::Initialize() {

}

void Weapon::Update(float deltaTime) {
	GameManager* mgr = GameManager::GetInstance();
	int wheelMax = 3;
	int wheelMin = 1;
	mousewheel += GetMouseWheelRotVol();
	
	if (mousewheel > wheelMax) {
		mousewheel = 1;
	}
	if (mousewheel < wheelMin) {
		mousewheel = 3;
	}
	/*if (mousewheel == HandGun) {
		HandGunFlag = true;
		SwitchWeapon(HandGun);
	}*/
	/*else HandGunFlag = false;*/
	if (mousewheel == SubMachineGun) {
		if (!SubMachineGunFlah) {
			reroadtime = sub_status.reroadtime;
			ammunition = sub_status.ammunition;
			maxAmmunition = sub_status.maxAmmunition;
			ammoClip = sub_status.ammoClip;
			maxAmmoClip = sub_status.maxAmmoClip;
			amountNeed = sub_status.amountNeed;
			ammoAvailable = sub_status.ammoAvailable;
			SubMachineGunFlah = true;
		}

		SwitchWeapon(SubMachineGun);
	}
	else SubMachineGunFlah = false;
	if (mousewheel == AssaultRifle) {
		if (!AssaultRifleFlag) {
			reroadtime = assault_status.reroadtime;
			ammunition = assault_status.ammunition;
			maxAmmunition = assault_status.maxAmmunition;
			ammoClip = assault_status.ammoClip;
			maxAmmoClip = assault_status.maxAmmoClip;
			amountNeed = assault_status.amountNeed;
			ammoAvailable = assault_status.ammoAvailable;
			AssaultRifleFlag = true;
		}
		SwitchWeapon(AssaultRifle);
	}
	else AssaultRifleFlag = false;
	if (mousewheel == HandGun) {
		if (!HandGunFlag) {
			reroadtime = hand_status.reroadtime;
			ammunition = hand_status.ammunition;
			maxAmmunition = hand_status.maxAmmunition;
			ammoClip = hand_status.ammoClip;
			maxAmmoClip = hand_status.maxAmmoClip;
			amountNeed = hand_status.amountNeed;
			ammoAvailable = hand_status.ammoAvailable;
			HandGunFlag = true;
		}
		SwitchWeapon(HandGun);
	}
	else HandGunFlag = false;
	if (GunReroad) {
		normalreroad_time += reroadtime;

		if (normalreroad_time >= 100) {
			ammunition -= ammoAvailable;
			ammoClip += ammoAvailable;
			normalreroad_time = 0;
			GunReroad = false;
		}

	}
	

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_R)) {
			amountNeed = maxAmmoClip - ammoClip;
			//マガジンに補充するべき弾薬数より所持してる弾薬数が大きいか
			ammoAvailable = amountNeed < ammunition ? amountNeed : ammunition;
			if (amountNeed != 0 && ammunition != 0) {
				if (!GunReroad)PlaySoundMem(HandGun_Reroad, DX_PLAYTYPE_BACK);
				GunReroad = true;
			}


		}
	
	
	

		
}

void Weapon::Render() {
	SetFontSize(55);
	//文字の描画
	//if (HandGunFlag) {
		DrawStringEx(840, 680, -1, "%2d", ammoClip);
		SetFontSize(40);
		DrawStringEx(895, 720, -1, "/%d", ammunition);

		DrawRotaGraph(775, 720, 0.15f, 0, NormalWeaponImage, true);
		DrawCircleGauge(reroad_x + 5, reroad_y + 8.5f, normalreroad_time, debug, 0.0f, 0.09f);
	//}
	DrawStringEx(840, 600, -1, "%d", mousewheel);
	//MATRIX view, proj;
	//memcpy(view.m, player_->GetCamera()->view_.m, sizeof(float) * 16);
	//memcpy(proj.m, player_->GetCamera()->proj_.m, sizeof(float) * 16);
	//SetCameraViewMatrix(view);
	//SetupCamera_ProjectionMatrix(proj);
	//DxLib::VECTOR vp;
	//vp = VGet(pos_.x, pos_.y, pos_.z);
	////rot_(tnl::Quaternion型)をMATRIX型に変換
	//MATRIX rot;
	//memcpy(rot.m, rot_.getMatrix().m, sizeof(float) * 16);

	//MV1SetRotationMatrix(ModelHandle, rot);
	//MV1SetScale(ModelHandle, { 1.0f,1.0f,1.0f });
	//MV1SetPosition(ModelHandle, vp);

	//MV1SetRotationXYZ(assault_status.AssaultModelHandle, VGet(angleX, angleY, 0.0f));
	//MV1SetScale(assault_status.AssaultModelHandle, { 1.0f,1.0f,1.0f });
	//MV1SetPosition(assault_status.AssaultModelHandle, VGet(x, y, z));

	//MV1SetRotationMatrix(hand_status.HandGunModelHandle, rot);
	//MV1SetScale(hand_status.HandGunModelHandle, { 1.0f,1.0f,1.0f });
	//MV1SetPosition(hand_status.HandGunModelHandle, vp);
	//// ３Ｄモデルの描画
	//MV1DrawModel(ModelHandle);
	//MV1DrawModel(assault_status.AssaultModelHandle);
	//MV1DrawModel(hand_status.HandGunModelHandle);
}

void Weapon::SwitchWeapon(WeaponType weapontype) {
	GameManager* mgr = GameManager::GetInstance();
	switch (weapontype) {
	case WeaponType::AssaultRifle:
		NormalWeaponImage = assault_status.AssaultRifleImage;
		NormalWeapon_Reroad = assault_status.AssaultRifle_Reroad;
		reroad_x = assault_status.reroad_x;
		reroad_y = assault_status.reroad_y;
		shoottime++;
		if (tnl::Input::IsMouseDown(tnl::Input::eMouse::LEFT) && !GunReroad && shoottime >= assault_status.shoottime) {

			if (ammoClip > 0) {
				PlaySoundMem(mgr->juusei, DX_PLAYTYPE_BACK);

				ammoClip--;
			}

			if (ammoClip <= 0) {
				ammoClip = 0;
				PlaySoundMem(Tama_0, DX_PLAYTYPE_BACK);
			}
			shoottime = 0;
		}
		break;
	case WeaponType::HandGun:
		NormalWeaponImage = hand_status.HandGunImage;
		NormalWeapon_Reroad = hand_status.HandGun_Reroad;
		reroad_x = hand_status.reroad_x;
		reroad_y = hand_status.reroad_y;
		shoottime++;
		if (tnl::Input::IsMouseTrigger(tnl::Input::eMouseTrigger::IN_LEFT) && !GunReroad && shoottime >= hand_status.shoottime) {
			
			if (ammoClip > 0) {
				PlaySoundMem(mgr->juusei, DX_PLAYTYPE_BACK);

				ammoClip--;
			}

			if (ammoClip <= 0) {
				ammoClip = 0;
				PlaySoundMem(Tama_0, DX_PLAYTYPE_BACK);
			}
			shoottime = 0;
		}
		break;
	case WeaponType::SubMachineGun:
		NormalWeaponImage = sub_status.SubMachineGunImage;
		NormalWeapon_Reroad = sub_status.SubMachinGun_Rrroad;
		reroad_x = sub_status.reroad_x;
		reroad_y = sub_status.reroad_y;
		shoottime++;
		if (tnl::Input::IsMouseDown(tnl::Input::eMouse::LEFT) && !GunReroad && shoottime >= sub_status.shoottime) {

			if (ammoClip > 0) {
				PlaySoundMem(mgr->juusei, DX_PLAYTYPE_BACK);

				ammoClip--;
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
//武器の描画ができてから
//void Weapon::Render(Player *p, int weapon, int type) {
//	auto prevWeapon = 0;
//	weapon = p->HaveWeapon[0];
//	type = HandGun;
//	/*if (tnl::Input::GetMouseWheel) {
//		prevWeapon = weapon;
//	}*/
//}