#pragma once
#include "gm_scene_base.h"
#include "../model/gm_parts.h"
#include "../gm_camera.h"
#include "../model/gm_airplane.h"
#include "../model/gm_model.h"

class GmCamera;
class SceneTutorial : public SceneBase {
public:
	SceneTutorial() {}
	~SceneTutorial() {}

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;
	GmCamera* camera_ = nullptr;

	int TutorialMusic = 0;
	int TutorialImage = 0;
	int TutorialBack = 0;
	int TutorialGuid = 0;

	float image_y = 0;


};
