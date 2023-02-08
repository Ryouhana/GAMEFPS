#include "../gm_manager.h"
#include "gm_scene_result.h"
#include "gm_scene_title.h"

void SceneResult::initialzie() {
	HelpImage = LoadGraph("graphics/help.jpg");
	//3D���f���̓ǂݍ���
	ModelHandle = MV1LoadModel("zombietaro/zombie.pmx");

	// �Đ����Ԃ̏�����
	PlayTime = 0.0f;
	// �R�c���f����1�Ԗڂ̃A�j���[�V�������A�^�b�`����
	AttachIndex = MV1AttachAnim(ModelHandle, 4, -1);
}

void SceneResult::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();


	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(0.1f, 1000.0f);

	//(0,10,-20)�̎��_����(0,10,0)�̃^�[�Q�b�g������p�x�ɃJ������ݒu
	SetCameraPositionAndTarget_UpVecY(VGet(0, 10, -20), VGet(0.0f, 10.0f, 0.0f));



	// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
	TotalTime = MV1GetAttachAnimTotalTime(ModelHandle, AttachIndex);




	if (tnl::Input::IsKeyDown(eKeys::KB_W)) {
		y -= 0.1f;
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_S)) {
		y += 0.1f;
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_A)) {
		x -= 0.1f;
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
		x += 0.1f;
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_Q)) {
		z -= 0.1f;
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_E)) {
		z += 0.1f;
	}

	if (tnl::Input::IsKeyDown(eKeys::KB_Z)) {
		angleY -= 0.1f;
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_X)) {
		angleY += 0.1f;
	}

	// �Đ����Ԃ�i�߂�
	PlayTime += 1;

	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		PlayTime = 0.0f;
	}

	// �Đ����Ԃ��Z�b�g����
	MV1SetAttachAnimTime(ModelHandle, AttachIndex, PlayTime);
	//�������̉�]�p�x���Z�b�g
	MV1SetRotationXYZ(ModelHandle, VGet(angleX, angleY, 0.0f));
	MV1SetScale(ModelHandle, { 1.0f,1.0f,1.0f });
	MV1SetPosition(ModelHandle, VGet(x, y, z));


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->chengeScene(new SceneTitle());
	}
}

void SceneResult::render()
{
	// �R�c���f���̕`��
	MV1DrawModel(ModelHandle);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "x=%.1f y=%.1f z=%.1f", x, y, z);
	/*DrawRotaGraph(520, 410, 0.9, 0, HelpImage,true);
	DrawStringEx(440, 50, -1, "������@");*/
}
