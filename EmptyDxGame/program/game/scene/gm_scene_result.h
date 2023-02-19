#include "gm_scene_base.h"
#include "../gm_camera.h"
#include "../model/Player.h"

class SceneResult : public SceneBase {
public:
	SceneResult() {}
	~SceneResult() {}

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	
	int AttachIndex = 0;
	int ModelMove1 = 0, ModelMove2 = 0, ModelMove3 = 0, ModelMove4 = 0;
	int HelpImage = 0;

	
	GmCamera* result_Camera = nullptr;
	

	float  TotalTime = 0, PlayTime = 0;
};
