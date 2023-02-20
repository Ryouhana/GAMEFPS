#include "gm_scene_base.h"
#include "../model/gm_parts.h"
#include "../gm_camera.h"
#include "../model/gm_airplane.h"
#include "../model/Player.h"
#include "../model/gm_model.h"

class GmCamera;
class SceneGameOver : public SceneBase {
public:
	SceneGameOver() {}
	~SceneGameOver() {}

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;
	GmCamera* camera_ = nullptr;

	int G_oImage = 0;
	int G_oRed = 0;
	int G_oSE = 0;
	int mouse_x = 0, mouse_y = 0;
	int m_x = 300, m_y = 500, m_x1 = 600, m_y1 = 500;
	int color = 0, color1 = 0;
	//ゲームオーバーシーンのカーソル画像
	int cursol_gameoverImage = 0;
	char	m_name[4] = {}, m_name1[5] = {};	// 項目名格納用変数




};