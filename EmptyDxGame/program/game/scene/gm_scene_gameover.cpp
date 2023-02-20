#include "../gm_manager.h"
#include "gm_scene_result.h"
#include "gm_scene_title.h"
#include "gm_scene_gameover.h"
#include "gm_scene_play.h"






void SceneGameOver::initialzie() {
	//画像の読み込み
	G_oImage = LoadGraph("graphics/gameover.jpg");
	G_oRed = LoadGraph("graphics/Red.png");
	G_oSE = LoadSoundMem("sound/");
	cursol_gameoverImage = LoadGraph("graphics/MouseTitle.png", true);
	
}

void SceneGameOver::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();
	//カーソルの位置取得
	GetMousePoint(&mgr->x, &mgr->y);



	GetMousePoint(&mouse_x, &mouse_y);	//マウスの座標取得
	if (m_x < mouse_x && mouse_x < m_x + 170 &&
		m_y < mouse_y && mouse_y < m_y + 50) // 文字列領域内
	{
		if (tnl::Input::IsMouseTrigger(tnl::Input::eMouseTrigger::IN_LEFT)) {
			mgr->chengeScene(new ScenePlay());
			StopSoundMem(mgr->ZombieSound);
		}
		color = RGB(0, 0, 200);
	}
	else {
		color = RGB(255, 255, 255);
	}
	if (m_x1 < mouse_x && mouse_x < m_x1 + 230 &&
		m_y1 < mouse_y && mouse_y < m_y1 + 50) // 文字列領域内
	{
		if (tnl::Input::IsMouseTrigger(tnl::Input::eMouseTrigger::IN_LEFT)) {
			mgr->chengeScene(new SceneTitle());
			StopSoundMem(mgr->ZombieSound);
		}
		color1 = RGB(0, 0, 200);
	}
	else {
		color1 = RGB(255, 255, 255);
	}



	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->chengeScene(new SceneTitle());
	}
}

void SceneGameOver::render()
{
	GameManager* mgr = GameManager::GetInstance();
	SetFontSize(50);
	
	

	DrawRotaGraph(500, 500, 2, 0, G_oRed, true);
	DrawRotaGraph(500, 380, 1, 0, G_oImage, true);
	DrawStringEx(m_x, m_y, color, "リトライ");
	DrawStringEx(m_x1, m_y1, color1, "タイトルへ");
	DrawRotaGraph(mgr->x, mgr->y, 0.2, 0, mgr->mouse_cursor, TRUE);
}