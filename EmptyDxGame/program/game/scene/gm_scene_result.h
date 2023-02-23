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

	

	int ModelMove1 = 0, ModelMove2 = 0, ModelMove3 = 0, ModelMove4 = 0;
	int HelpImage = 0;

	int testModel = 0;
	GmCamera* result_Camera = nullptr;
	tnl::Vector3 testpos_;
	tnl::Quaternion testrot_;
	

};
