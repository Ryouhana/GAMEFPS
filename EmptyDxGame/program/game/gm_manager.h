#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class SceneBase;
class GameManager {
private:
	GameManager();
	~GameManager();

	int img_black_ = 0;

	static GameManager* instance_;

	// 画面遷移演出の時間
	const float SCENE_TRANSITION_FIX_TIME = 0.5f;
	float scene_transition_time_ = 0;
	float scene_transition_alpha_ = 1.0f;

	tnl::Sequence<GameManager> sequence_ =
		tnl::Sequence<GameManager>(this, &GameManager::seqSceneInTransition);
	// 画面遷移( フェードインプロセス )
	bool seqSceneInTransition(const float delta_time);

	// ゲームプロセス
	bool seqGameProcess(const float delta_time);

	// 画面遷移( フェードアウトプロセス )
	bool seqSceneOutTransition(const float delta_time);

	// 現在のシーン
	SceneBase* scene_now_ = nullptr;
	// 予約シーン
	SceneBase* scene_next_ = nullptr;

public:

	// インスタンスの取得
	static GameManager* GetInstance();

	// 破棄
	static void Destroy();

	// 更新
	void update(float delta_time);

	// シーンの変更
	// arg1... SceneBase を継承したクラスインスタンス
	void chengeScene(SceneBase* next);




public:

	// ゲーム全体で参照したい変数はここで用意
#define MENU_STRING_COLOR_NORMAL	GetColor( 255, 255, 255 )	// メニュー項目文字列カラー（通常）
#define MENU_STRING_COLOR_OVER		GetColor(   255, 0,   0 )	// メニュー項目文字列カラー（マウスオーバー）
#define MENU_STRING_COLOR_CLICK		GetColor(   100,   0, 0 )	// メニュー項目文字列カラー（クリック）
#define MENU_STRING_COLOR_ERROR		GetColor( 255,   0,   0 )	// メニュー項目文字列カラー（エラー）

#define MENU_NUM					3							// メニュー項目数
#define MENU_STRING_SIZE			50	


	int title_back = 0;
	int mouse_cursor = 0;
	int background = 0;
	int Mouse = 0;
	int juge = 0;
	int x = 0, y = 0;
	int m_state_c = 0;
	int juukon = 0;
	int juusei = 0, juudan = 0;
	int juuim = 0;
	int ZombieSound = 0;
	int TitleMusic = 0;




	float box_x[5] = { -175,-175,-175,-160,-130 }, box_y[5] = { 90,50,0,-35,-40 }, box_z[3] = { -30,-80,-1 };
	float c_x = 0, c_y = 0, c_z = 0;
	float fadeout = 255;

	bool juu_init = false;


};
