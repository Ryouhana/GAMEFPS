#pragma once
#include "../dxlib_ext/dxlib_ext_camera.h"

class GmCamera : public dxe::Camera {
public:
	GmCamera() : dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT) {}
	~GmCamera() {}
	tnl::Vector3 free_look_angle_xy_ = { tnl::ToRadian(30), 0, 0 };
	float target_distance_ = 300;
	enum {
		CTRL_TYPE_QTN,
		CTRL_TYPE_FREE_LOOK
	};
	int ctrl = 0;
	tnl::Quaternion c_rot;
	void update();
};

