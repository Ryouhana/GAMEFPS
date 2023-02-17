#include "Player.h"
using namespace std;

Player::Player(tnl::Vector3 pos)
{
	
	mainCamera = new GmCamera();
	mainCamera->ctrl = GmCamera::CTRL_TYPE_QTN;
	mainCamera->pos_ = pos;//{ 100, 60, 0 };
	body = dxe::Mesh::CreateSphereMV(30);
	Walk_SE = LoadSoundMem("sound/Walk_SE.mp3");
	Run_SE = LoadSoundMem("sound/Run_SE.mp3");
	
}

void Player::Initialize(tnl::Vector3 pos)
{
	mainCamera = new GmCamera();
	mainCamera->ctrl = GmCamera::CTRL_TYPE_QTN;
	mainCamera->pos_ = pos;//{ 100, 60, 0 };
	/*Walk_SE = LoadSoundMem("sound/Walk_SE.mp3");
	Run_SE = LoadSoundMem("sound/Run_SE.mp3");*/
	body = dxe::Mesh::CreateSphereMV(30);
	

}

float timer = 0;
tnl::Vector3 msv = { DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 0 };
void Player::Update(float deltaTime)
{

	CameraAngle();

	// プレイヤーのダッシュ処理
	if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT) && tnl::Input::IsKeyDown(eKeys::KB_W)) {
		if (hp != 0) {
			if (stamina > 0.f) {
				dushFlag = true;

			}
		}
		

	}
	else {

		dushFlag = false;
	}
	if (stamina <= 0.f) {

		dushFlag = false;

	}
	if (!dushFlag) {
		RecoveryStamina(deltaTime);
	}
	// プレイヤーの移動処理関数（HPが0になったら実行されない）
	if (hp > 0) {
		Move(0);
	}
	else {
		walkFlag = false;
		dushFlag = false;
	}

	//歩いてる時の足音
	if (walkFlag) {
		PlaySoundMem(Walk_SE, DX_PLAYTYPE_LOOP, 0);
	}
	//歩いてる音を止める
	if (!walkFlag || dushFlag) {
		StopSoundMem(Walk_SE);
	}
	//走ってる時の足音
	if (dushFlag) {
		PlaySoundMem(Run_SE, DX_PLAYTYPE_LOOP, 0);
	}
	//走ってる音を止める
	if (!dushFlag) {
		StopSoundMem(Run_SE);
	}

	// プレイヤーのジャンプ処理
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		jumpFlag = true;
	}

	//レイのやつ
	/*tnl::Vector3 ray = tnl::Vector3::CreateScreenRay(
		msv.x,
		msv.y,
		mainCamera->screen_w_,
		mainCamera->screen_h_,
		mainCamera->view_,
		mainCamera->proj_);*/
}

void Player::Render()
{
	mainCamera->update();
	DrawGridGround(mainCamera, 50, 20);

}

tnl::Vector3 Player::GetPostion()
{
	return mainCamera->pos_;
}

GmCamera* Player::GetCamera()
{
	return mainCamera;
}

void Player::Move(int i)
{

		moveDirection[0] = mainCamera->front().xz();
		moveDirection[1] = mainCamera->right().xz();
		moveDirection[2] = mainCamera->back().xz();
		moveDirection[3] = mainCamera->left().xz();
	

	tnl::Vector3 move_direction;
	tnl::Input::RunIndexKeyDown([&](uint32_t idx) {
		move_direction += moveDirection[idx];


		}, eKeys::KB_W, eKeys::KB_D, eKeys::KB_S, eKeys::KB_A);

	move_direction.normalize();

	if (tnl::Input::IsKeyDown(eKeys::KB_W, eKeys::KB_A, eKeys::KB_S, eKeys::KB_D)) {
		walkFlag = true;

	}

	else if (!tnl::Input::IsKeyDown(eKeys::KB_W, eKeys::KB_A, eKeys::KB_S, eKeys::KB_D)) {
		walkFlag = false;

	}

	if (dushFlag) {
		timer = 0.f;
		Dush(i);
	}

	else mainCamera->pos_ += move_direction * walkSpeed;

	mainCamera->pos_.x = clamp(mainCamera->pos_.x,
		(float)-fieldMax,
		(float)fieldMax);
	mainCamera->pos_.z = clamp(mainCamera->pos_.z,
		(float)-fieldMax,
		(float)fieldMax);

	body->pos_ = mainCamera->pos_;

}

void Player::Dush(int i)
{
	mainCamera->pos_ += moveDirection[i] * dushSpeed;
	stamina -= 0.5f;
	stamina = max(stamina, 0.f);
}

void Player::Jump()
{
	//
}

void Player::RecoveryStamina(float deltaTime)
{
	timer += deltaTime;
	if (timer > dushRecoveryTime) {
		stamina += 1;
		stamina = min(stamina, staminaMax);
	}
}

void Player::CameraAngle()
{
	tnl::Vector3 mv = tnl::Input::GetMouseVelocity();
	float length = mv.length();
	mv.normalize();
	if (length > 2.0f) {

		tnl::Vector3 v = { mv.x, -mv.y, mv.z };
		tnl::Vector3 front = mainCamera->front();
		tnl::Vector3 v_scr = tnl::Vector3::TransformCoord(v, mainCamera->c_rot);
		tnl::Vector3 axis = tnl::Vector3::Cross(front, v_scr);

		tnl::Vector3 front_xz = front.xz();
		float angle = front_xz.angle(front);

		bool is_look_up = (front.y > 0) ? true : false;
		bool is_mouse_up = (mv.y < 0) ? true : false;

		if ((is_look_up && is_mouse_up) || (!is_look_up && !is_mouse_up)) {
			if (tnl::ToDegree(angle) < 70) {
				mainCamera->c_rot *= tnl::Quaternion::RotationAxis(axis, tnl::ToRadian(length * 0.1f));
			}
		}

		else {
			mainCamera->c_rot *= tnl::Quaternion::RotationAxis(axis, tnl::ToRadian(length * 0.1f));
		}
	}
}

void Player::HitPoint() {

}

