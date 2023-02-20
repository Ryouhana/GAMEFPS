#include "weapon.h"
#include "../gm_manager.h"
#include "../model/Player.h"
using namespace std;

Weapon::Weapon() {
	hand_status.HandGunImage = LoadGraph("graphics/Handgun.png");
	sub_status.SubMachineGunImage = LoadGraph("graphics/MP5.png");
	assault_status.AssaultRifleImage = LoadGraph("graphics/XM177.png");
	
	assault_status.AssaultModelHandle = MV1LoadModel("XM177/Xm177.pmx");
	Tama_0 = LoadSoundMem("sound/Gun_SE/no.mp3");
	HandGun_Reroad = LoadSoundMem("sound/Gun_SE/HandgunReroad.mp3");
	debug = LoadGraph("graphics/Ring.png");
	weapon = new GmCamera;
}
void Weapon::Initialize() {
	hand_status.HandGunModelHandle = MV1LoadModel("MEUPistol/MEUPistol.pmd");
	//Še•Ší‚ÌŠŽ’e–ò‚Æƒ}ƒKƒWƒ““à‚Ì’e–ò‚ÌƒXƒe[ƒ^ƒX‚ð‰¼‚Ì•Ï”‚Éˆê“x‚¾‚¯‘ã“ü
	demo_assaultammoClip = assault_status.ammoClip;
	demo_assaultammunition = assault_status.ammunition;
	demo_subammoClip = sub_status.ammoClip;
	demo_subammunition = sub_status.ammunition;
	demo_handammoClip = hand_status.ammoClip;
	demo_handammunition = hand_status.ammunition;

	

}

void Weapon::Update(float deltaTime) {
	GameManager* mgr = GameManager::GetInstance();
	
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
	/*if (mousewheel == HandGun) {
		HandGunFlag = true;
		SwitchWeapon(HandGun);
	}*/
	/*else HandGunFlag = false;*/
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

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_R)) {

		amountNeed = maxAmmoClip - ammoClip;
		//ƒ}ƒKƒWƒ“‚É•â[‚·‚é‚×‚«’e–ò”‚æ‚èŠŽ‚µ‚Ä‚é’e–ò”‚ª‘å‚«‚¢‚©
		ammoAvailable = amountNeed < ammunition ? amountNeed : ammunition;

		if (amountNeed != 0 && ammunition != 0) {
			if (!GunReroad)PlaySoundMem(HandGun_Reroad, DX_PLAYTYPE_BACK);
			GunReroad = true;

		}
	}
	if (GunReroad) {
		normalreroad_time += reroadtime;

		if (normalreroad_time >= 100) {
			ammunition -= ammoAvailable;
			ammoClip += ammoAvailable;
			//•Ší‚ðØ‚è‘Ö‚¦‚Ä‚àƒŠƒ[ƒhŒã‚Ì’e”‚É‚È‚é
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
	

		
		
}

void Weapon::Render() {
	weapon->update();
	
	SetFontSize(55);
	//•¶Žš‚Ì•`‰æ
	//if (HandGunFlag) {
		DrawStringEx(840, 680, -1, "%2d", ammoClip);
		SetFontSize(40);
		DrawStringEx(895, 720, -1, "/%d", ammunition);

		DrawRotaGraph(weapon_x, weapon_y, weapon_scale, 0, NormalWeaponImage, true);
		DrawCircleGauge(reroad_x + 5, reroad_y + 8.5f, normalreroad_time, debug, 0.0f, 0.09f);
	//}
	DrawStringEx(840, 600, -1, "%d", mousewheel);
	
	
	if (tnl::Input::IsKeyDown(eKeys::KB_UP)) {
		pos_.y -= 0.1f;
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_DOWN)) {
		pos_.y += 0.1f;
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_LEFT)) {
		pos_.x -= 0.1f;
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) {
		pos_.x += 0.1f;
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_Q)) {
		pos_.z -= 0.1f;
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_E)) {
		pos_.z += 0.1f;
	}
	int x = 1, y = 1;
	if (tnl::Input::IsKeyDown(eKeys::KB_Z)) {
		
		
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_X)) {
		rot_ *= tnl::Quaternion::RotationAxis({ 0,1,0 },tnl::ToRadian(1));
	}
	MATRIX view, proj;
	memcpy(view.m, weapon->view_.m, sizeof(float) * 16);
	memcpy(proj.m, weapon->proj_.m, sizeof(float) * 16);
	SetCameraViewMatrix(view);
	SetupCamera_ProjectionMatrix(proj);
	DxLib::VECTOR vp;
	vp = VGet(pos_.x, pos_.y, pos_.z);
	//rot_(tnl::QuaternionŒ^)‚ðMATRIXŒ^‚É•ÏŠ·
	MATRIX rot;
	memcpy(rot.m, rot_.getMatrix().m, sizeof(float) * 16);

	
	/*MV1SetRotationXYZ(assault_status.AssaultModelHandle, VGet(angleX, angleY, 0.0f));
	MV1SetScale(assault_status.AssaultModelHandle, { 1.0f,1.0f,1.0f });
	MV1SetPosition(assault_status.AssaultModelHandle, VGet(x, y, z));*/

	MV1SetRotationMatrix(hand_status.HandGunModelHandle, rot);
	MV1SetScale(hand_status.HandGunModelHandle, { 1.0f,1.0f,1.0f });
	MV1SetPosition(hand_status.HandGunModelHandle, vp);
	// ‚R‚cƒ‚ƒfƒ‹‚Ì•`‰æ
	
	//MV1DrawModel(assault_status.AssaultModelHandle);
	
	DrawFormatString(0, 0, GetColor(255, 255, 255), "x=%.1f y=%.1f z=%.1f", pos_.x, pos_.y, pos_.z);
	DrawFormatString(0, 200, GetColor(255, 255, 255), "x=%.1f y=%.1f", rot_.x, rot_.y);
	
}

void Weapon::SwitchWeapon(WeaponType weapontype) {
	GameManager* mgr = GameManager::GetInstance();
	switch (weapontype) {
	case WeaponType::AssaultRifle:
		NormalWeaponImage = assault_status.AssaultRifleImage;
		NormalWeapon_Reroad = assault_status.AssaultRifle_Reroad;
		reroad_x = assault_status.reroad_x;
		reroad_y = assault_status.reroad_y;
		//ƒAƒTƒ‹ƒgƒ‰ƒCƒtƒ‹‚Ì‰æ‘œˆÊ’u‚Æ‘å‚«‚³‚ð‘ã“ü
		weapon_x = assault_status.weapon_x;
		weapon_y = assault_status.weapon_y;
		weapon_scale = assault_status.weapon_scale;
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
		rot_ = tnl::Quaternion::RotationAxis({ 0,1,0 }, tnl::ToRadian(180));
		pos_.x = 1.2f, pos_.y = -1.2f, pos_.z = -96.6f;
		NormalWeaponImage = hand_status.HandGunImage;
		NormalWeapon_Reroad = hand_status.HandGun_Reroad;
		reroad_x = hand_status.reroad_x;
		reroad_y = hand_status.reroad_y;
		//ƒnƒ“ƒhƒKƒ“‚Ì‰æ‘œˆÊ’u‚Æ‘å‚«‚³‚ð‘ã“ü
		weapon_x = hand_status.weapon_x;
		weapon_y = hand_status.weapon_y;
		weapon_scale = hand_status.weapon_scale;
		shoottime++;
		if (tnl::Input::IsMouseTrigger(tnl::Input::eMouseTrigger::IN_LEFT) && !GunReroad && shoottime >= hand_status.shoottime) {
			
			if (ammoClip > 0) {
				PlaySoundMem(mgr->juusei, DX_PLAYTYPE_BACK);

				ammoClip--;
				if (mousewheel == HandGun) {
					demo_handammoClip = ammoClip;
				}
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
		//ƒTƒuƒ}ƒVƒ“ƒKƒ“‚Ì‰æ‘œˆÊ’u‚Æ‘å‚«‚³‚ð‘ã“ü
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
//•Ší‚Ì•`‰æ‚ª‚Å‚«‚Ä‚©‚ç
//void Weapon::Render(Player *p, int weapon, int type) {
//	auto prevWeapon = 0;
//	weapon = p->HaveWeapon[0];
//	type = HandGun;
//	/*if (tnl::Input::GetMouseWheel) {
//		prevWeapon = weapon;
//	}*/
//}