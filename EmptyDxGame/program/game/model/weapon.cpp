#include "weapon.h"
using namespace std;

Weapon::Weapon() {
	HandGunImage = LoadGraph("graphics/Handgun.png");
}
void Weapon::Initialize() {

}

void Weapon::Update(float deltaTime) {
	int wheelMax = 3;
	int wheelMin = 1;
	mousewheel += GetMouseWheelRotVol();

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

}

void Weapon::Render() {
	SetFontSize(55);
	//•¶Žš‚Ì•`‰æ
	if (HandGunFlag) {
		DrawStringEx(840, 680, -1, "%2d", ammoClip);
		SetFontSize(40);
		DrawStringEx(895, 720, -1, "/%d", ammunition);

		DrawRotaGraph(775, 720, 0.15f, 0, HandGunImage, true);
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