#include "../gm_manager.h"
#include "gm_scene_result.h"
#include "gm_scene_title.h"
#include "gm_scene_tutorial.h"
#include "gm_scene_play.h"

void SceneTutorial::initialzie() {
	TutorialMusic = LoadSoundMem("sound/Gun_SE/sensou.mp3");
	TutorialImage = LoadGraph("graphics/bun.png");
	TutorialBack = LoadGraph("graphics/sensou.jpg");
	TutorialGuid = LoadGraph("graphics/enter.png");
	PlaySoundMem(TutorialMusic, DX_PLAYTYPE_BACK);
	image_y = 1200;
}

void SceneTutorial::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();
	int i = 0;

	if (image_y < 540) {
		image_y = 540;


	}
	else if (image_y > 540) {
		image_y -= 0.3f;
		if (tnl::Input::IsKeyDown(eKeys::KB_SPACE)) {
			image_y -= 5.f;
		}
	}

}

void SceneTutorial::render()
{
	GameManager* mgr = GameManager::GetInstance();
	DrawRotaGraph(530, 480, 0.9, 0, TutorialBack, true);
	DrawRotaGraph(530, image_y, 0.9, 0, TutorialImage, true);
	if (image_y == 540.f) {


		DrawRotaGraph(870, 400, 1.5, 0, TutorialGuid, true);
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			mgr->chengeScene(new ScenePlay());
		}

	}

}
