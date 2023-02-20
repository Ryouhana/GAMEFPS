#include "../gm_manager.h"
#include "gm_scene_result.h"
#include "gm_scene_title.h"


void SceneResult::initialzie() {
	
	HelpImage = LoadGraph("graphics/help.jpg");

	//3D���f���̓ǂݍ���
	
	
	
	// �Đ����Ԃ̏�����
	PlayTime = 0.0f;
	// �R�c���f����1�Ԗڂ̃A�j���[�V�������A�^�b�`����
	//>>>>>AttachIndex = MV1AttachAnim(ModelHandle, 4, -1);
	result_Camera = new GmCamera();
	result_Camera->pos_ = { 0,50,-100 };
}

void SceneResult::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();
	

	// Update the camera
	
	

	//pos_(tnl::Vector3�^)��DxLib_VECTOR�^�ɕϊ�
	
	/*DxLib::VECTOR cp;
	cp = VGet(result_Camera->pos_.x, result_Camera->pos_.y, result_Camera->pos_.z);
	cp = {pos_.x,pos_.y,pos_.z};*/
	////���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
	//SetCameraNearFar(0.1f, 1000.0f);

	////(0,10,-20)�̎��_����(0,10,0)�̃^�[�Q�b�g������p�x�ɃJ������ݒu
	//SetCameraPositionAndTarget_UpVecY(VGet(0, 10, -20), VGet(0.0f, 10.0f, 0.0f));



	// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
	//>>>>>TotalTime = MV1GetAttachAnimTotalTime(ModelHandle, AttachIndex);




	//if (tnl::Input::IsKeyDown(eKeys::KB_W)) {
	//	pos_.y -= 0.1f;
	//}
	//else if (tnl::Input::IsKeyDown(eKeys::KB_S)) {
	//	pos_.y += 0.1f;
	//}
	//else if (tnl::Input::IsKeyDown(eKeys::KB_A)) {
	//	pos_.x -= 0.1f;
	//}
	//else if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
	//	pos_.x += 0.1f;
	//}
	//else if (tnl::Input::IsKeyDown(eKeys::KB_Q)) {
	//	pos_.z -= 0.1f;
	//}
	//else if (tnl::Input::IsKeyDown(eKeys::KB_E)) {
	//	pos_.z += 0.1f;
	//}

	//if (tnl::Input::IsKeyDown(eKeys::KB_Z)) {
	//	rot_ *= tnl::Quaternion::RotationAxis({ 1,0,0 }, tnl::ToRadian(5));
	//}
	//else if (tnl::Input::IsKeyDown(eKeys::KB_X)) {
	//	rot_ *= tnl::Quaternion::RotationAxis({ 0,1,0 },tnl::ToRadian(5));
	//}

	// �Đ����Ԃ�i�߂�
	PlayTime += 1;

	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		PlayTime = 0.0f;
	}

	// �Đ����Ԃ��Z�b�g����
	//>>>>>>MV1SetAttachAnimTime(ModelHandle, AttachIndex, PlayTime);
	//�������̉�]�p�x���Z�b�g
	

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->chengeScene(new SceneTitle());
	}
}

void SceneResult::render()
{

	result_Camera->update();
	

	/*ModelHandle->render(result_Camera);*/
	

	

	
	/*DrawRotaGraph(520, 410, 0.9, 0, HelpImage,true);
	DrawStringEx(440, 50, -1, "������@");*/
}
