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

	int ModelHandle = 0, AttachIndex = 0;
	int ModelMove1 = 0, ModelMove2 = 0, ModelMove3 = 0, ModelMove4 = 0;
	int HelpImage = 0;
	int AssaultModelHandle = 0;
	GmCamera* result_Camera = nullptr;

	tnl::Quaternion rot_;
	tnl::Vector3 pos_;
	Player* player_ = nullptr;
	float x = 0, y = 0, z = 0;
	float angleX = 0, angleY = 0, angleZ = 0;
	float  TotalTime = 0, PlayTime = 0;
};
