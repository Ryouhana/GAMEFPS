#include "../gm_manager.h"
#include "gm_scene_title.h"
#include "gm_scene_play.h"
#include "gm_scene_tutorial.h"
#include "../model/gm_parts.h"
#include "../../dxlib_ext/dxlib_ext.h"
#include "../gm_camera.h"
#include "../model/gm_airplane.h"
#include "../model/gm_model.h"
#include "gm_scene_result.h"



//--------------------------------------------
//メニュー選択の処理の実行
//--------------------------------------------

// メニュー項目のクラス
class C_MenuElement
{
public:
	// コンストラクタ
	C_MenuElement(const char* name, int x, int y)
	{
		strcpy(m_name, name);
		m_x = x;
		m_y = y;
	}
	~C_MenuElement() {};
	tnl::Quaternion rot_;
	// 更新処理
	void Update(void)
	{
		GameManager* mgr = GameManager::GetInstance();
		int mouse_x, mouse_y;
		ChangeVolumeSoundMem(160, mgr->juusei);

		GetMousePoint(&mouse_x, &mouse_y);	//マウスの座標取得
		if (m_x < mouse_x && mouse_x < m_x + GetDrawStringWidth(m_name, strlen(m_name)) &&
			m_y < mouse_y && mouse_y < m_y + MENU_STRING_SIZE)	// 文字列領域内
		{
			if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {	// 押されている
				m_state = 2;
				if (m_state == 2 && m_y == 350) {

					mgr->chengeScene(new ScenePlay());
					StopSoundMem(mgr->TitleMusic);
					StopSoundMem(mgr->juudan);
					StopSoundMem(mgr->juusei);

				}
				if (m_state == 2 && m_y == 450) {
					mgr->chengeScene(new SceneResult());
				}

				if (m_state == 2) {
					mgr->juuim = 1;
					if (mgr->juuim == 1) {
						DrawRotaGraph(mgr->x, mgr->y, 2, 0, mgr->juukon, true);
					}
					PlaySoundMem(mgr->juusei, DX_PLAYTYPE_BACK);
					PlaySoundMem(mgr->juudan, DX_PLAYTYPE_BACK);


				}
				if (m_state == 2 && m_y == 550) {
					DxLib_End();
				}

			}
			else													// 押されてない
				m_state = 1;


			if (m_state == 1) {
				mgr->m_state_c = 1;
			}
			else { mgr->m_state_c = 0; }

		}
		else													// 領域外
			m_state = 0;
		if (m_state == 0) {
			mgr->c_x = mgr->c_x;
			mgr->c_y = mgr->c_y;
			mgr->c_z = mgr->c_z;
		}
	}

	// 描画処理
	void Draw(void)
	{
		int string_color;

		switch (m_state)
		{
		case 0:		string_color = MENU_STRING_COLOR_NORMAL;	break;
		case 1:		string_color = MENU_STRING_COLOR_OVER;

			break;
		case 2:		string_color = MENU_STRING_COLOR_CLICK;		break;
		default:	string_color = MENU_STRING_COLOR_ERROR;		break;
		}

		DrawString(m_x, m_y, m_name, string_color);
	}

private:

	char	m_name[128];	// 項目名格納用変数
	int		m_x, m_y;		// 座標格納用変数
	int m_state = 0;        // 0:初期状態 1:オンマウス 2:クリックされた
	float box_angle = 0;
};


//-------------------------------------------------
//メニュー選択文字の描画
// ------------------------------------------------


class C_Menu
{
public:

	// コンストラクタ
	C_Menu(void)
	{
		const char* menu_name[MENU_NUM] = { "ゲームスタート",  "ヘルプ",  "ゲーム終了" };
		const int menu_y[MENU_NUM] = { 350, 450, 550 };

		// メニュー項目を５つ作成（クラス配列動的確保）
		for (int i = 0; i < MENU_NUM; i++)
			menu_element[i] = new C_MenuElement(menu_name[i], 100 + 30 * i, menu_y[i]);
	}

	// デストラクタ
	~C_Menu(void)
	{
		// クラス配列解放
		for (int i = 0; i < MENU_NUM; i++)
			delete menu_element[i];
	}

	// 更新処理
	void Update(void)
	{
		for (int i = 0; i < MENU_NUM; i++)
			menu_element[i]->Update();



	}

	// 描画処理
	void Draw(void)
	{
		for (int i = 0; i < MENU_NUM; i++)
			menu_element[i]->Draw();
	}

private:

	C_MenuElement* menu_element[MENU_NUM];		// メニュー項目のクラスポインタ
};






void SceneTitle::initialzie() {



	//ーーーーーータイトル画面のゲームカメラを実行ーーーーーー
	camera_ = new GmCamera();
	camera_->ctrl = GmCamera::CTRL_TYPE_FREE_LOOK;
	camera_->pos_ = { 0, 0, -300 };

	rot_1 = new Model();




}






void SceneTitle::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();

	// ーーーーーーーBGMの再生ーーーーーーーーー
	if (!music) {
		mgr->TitleMusic = LoadSoundMem("sound/desperate.mp3");
		PlaySoundMem(mgr->TitleMusic, DX_PLAYTYPE_NORMAL + DX_PLAYTYPE_LOOP);
		MovieGraphHandle = LoadGraph("movie/tuki.mp4");


		music = true;
	}

	SetMouseDispFlag(FALSE);

	if (!init) {

		mgr->mouse_cursor = LoadGraph("graphics/MouseTitle.png", true);
		mgr->juukon = LoadGraph("graphics/konn.png");
		mgr->juusei = LoadSoundMem("sound/sen_ge_gun12.mp3");
		mgr->juudan = LoadSoundMem("sound/Gun_SE/juudan.mp3");
		init = true;

	}



	GetMousePoint(&mgr->x, &mgr->y);                //マウスの座標取得

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

		StopSoundMem(mgr->TitleMusic);
		mgr->chengeScene(new SceneTutorial());

		SetFontSize(20);
	}
	DrawLineBox(100, 100, 100, 100, BACKGROUND_BLUE);

}




void SceneTitle::render()
{

	//ーーーーーーダウンロードしたフォントの読み込みーーーーーーーー
	LPCSTR font_path = "./ankokuzonji/Zomzi.TTF";

	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}

	ChangeFont("暗黒ゾン字", DX_CHARSET_DEFAULT);
	GameManager* mgr = GameManager::GetInstance();
	C_Menu menu;


	camera_->update();


	PlayMovieToGraph(MovieGraphHandle);
	DrawExtendGraph(0, 0, 1080, 800, MovieGraphHandle, FALSE);

	// カーソル合わせによりボックスの移動処理



	// 更新フェーズ 
	menu.Update();

	// 描画フェーズ
	menu.Draw();


	// カーソルに合わせて動く画像の描画処理

	DrawRotaGraph(mgr->x, mgr->y, 0.2, 0, mgr->mouse_cursor, TRUE);

	SetFontSize(100);
	DrawStringEx(100, 30, RGB(0, 0, 200), "Ｚ World Survaival");
	SetFontSize(50);

}
