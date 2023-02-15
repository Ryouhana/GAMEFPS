#include "weapon.h"
#include "../gm_manager.h"
using namespace std;

Weapon::Weapon() {
	HandGunImage = LoadGraph("graphics/Handgun.png");
	Tama_0 = LoadSoundMem("sound/Gun_SE/no.mp3");
	HandGun_Reroad = LoadSoundMem("sound/Gun_SE/HandgunReroad.mp3");
	debug = LoadGraph("graphics/Ring.png");
}
void Weapon::Initialize() {

}

void Weapon::Update(float deltaTime) {
	GameManager* mgr = GameManager::GetInstance();
	int wheelMax = 3;
	int wheelMin = 1;
	mousewheel += GetMouseWheelRotVol();
	if (GunReroad) {
		debug_i += 2.0f;

		if (debug_i >= 100) {
			ammunition -= ammoAvailable;
			ammoClip += ammoAvailable;
			debug_i = 0;
			GunReroad = false;
		}

	}
		if (mousewheel > wheelMax) {
			mousewheel = 1;
		}
		if (mousewheel < wheelMin) {
			mousewheel = 3;
		}
		if (mousewheel == wheelMin) {
			HandGunFlag = true;
		}
		else HandGunFlag = false;
		if (HandGunFlag) {
			if (tnl::Input::IsMouseTrigger(tnl::Input::eMouseTrigger::IN_LEFT) && !GunReroad) {
				if (ammoClip > 0) {
					PlaySoundMem(mgr->juusei, DX_PLAYTYPE_BACK);

					ammoClip--;
				}

				if (ammoClip <= 0) {
					ammoClip = 0;
					PlaySoundMem(Tama_0, DX_PLAYTYPE_BACK);
				}
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
		
		}
}

void Weapon::Render() {
	SetFontSize(55);
	//•¶Žš‚Ì•`‰æ
	if (HandGunFlag) {
		DrawStringEx(840, 680, -1, "%2d", ammoClip);
		SetFontSize(40);
		DrawStringEx(895, 720, -1, "/%d", ammunition);

		DrawRotaGraph(775, 720, 0.15f, 0, HandGunImage, true);
		DrawCircleGauge(reroad_x + 5, reroad_y + 8.5f, debug_i, debug, 0.0f, 0.08f);
	}
	DrawStringEx(840, 600, -1, "%d", mousewheel);
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