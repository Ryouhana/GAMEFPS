#include "gm_scene_base.h"
#include "../model/gm_parts.h"
#include "../gm_camera.h"
#include "../model/gm_airplane.h"
#include "../model/gm_model.h"

class GmCamera;
class SceneTitle : public SceneBase {
public:
	SceneTitle() {}
	~SceneTitle() {}

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;
	GmCamera* camera_ = nullptr;

	Model* rot_1 = nullptr;
	dxe::Mesh* dome = nullptr;
	dxe::Mesh* plate = nullptr;


	Model* obj_ = nullptr;




	bool init = false;
	bool s_init = false;
	bool music = false;

	int MovieGraphHandle = 0;
	int randMusic = 0;

};
