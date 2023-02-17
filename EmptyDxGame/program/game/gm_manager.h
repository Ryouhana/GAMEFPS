#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class SceneBase;
class GameManager {
private:
	GameManager();
	~GameManager();

	int img_black_ = 0;

	static GameManager* instance_;

	// ��ʑJ�ډ��o�̎���
	const float SCENE_TRANSITION_FIX_TIME = 0.5f;
	float scene_transition_time_ = 0;
	float scene_transition_alpha_ = 1.0f;

	tnl::Sequence<GameManager> sequence_ =
		tnl::Sequence<GameManager>(this, &GameManager::seqSceneInTransition);
	// ��ʑJ��( �t�F�[�h�C���v���Z�X )
	bool seqSceneInTransition(const float delta_time);

	// �Q�[���v���Z�X
	bool seqGameProcess(const float delta_time);

	// ��ʑJ��( �t�F�[�h�A�E�g�v���Z�X )
	bool seqSceneOutTransition(const float delta_time);

	// ���݂̃V�[��
	SceneBase* scene_now_ = nullptr;
	// �\��V�[��
	SceneBase* scene_next_ = nullptr;

public:

	// �C���X�^���X�̎擾
	static GameManager* GetInstance();

	// �j��
	static void Destroy();

	// �X�V
	void update(float delta_time);

	// �V�[���̕ύX
	// arg1... SceneBase ���p�������N���X�C���X�^���X
	void chengeScene(SceneBase* next);




public:

	// �Q�[���S�̂ŎQ�Ƃ������ϐ��͂����ŗp��
#define MENU_STRING_COLOR_NORMAL	GetColor( 255, 255, 255 )	// ���j���[���ڕ�����J���[�i�ʏ�j
#define MENU_STRING_COLOR_OVER		GetColor(   255, 0,   0 )	// ���j���[���ڕ�����J���[�i�}�E�X�I�[�o�[�j
#define MENU_STRING_COLOR_CLICK		GetColor(   100,   0, 0 )	// ���j���[���ڕ�����J���[�i�N���b�N�j
#define MENU_STRING_COLOR_ERROR		GetColor( 255,   0,   0 )	// ���j���[���ڕ�����J���[�i�G���[�j

#define MENU_NUM					3							// ���j���[���ڐ�
#define MENU_STRING_SIZE			50	


	int title_back = 0;
	int mouse_cursor = 0;
	int background = 0;
	int Mouse = 0;
	int juge = 0;
	int x = 0, y = 0;
	int m_state_c = 0;
	int juukon = 0;
	int juusei = 0, juudan = 0;
	int juuim = 0;
	int ZombieSound = 0;
	int TitleMusic = 0;




	float box_x[5] = { -175,-175,-175,-160,-130 }, box_y[5] = { 90,50,0,-35,-40 }, box_z[3] = { -30,-80,-1 };
	float c_x = 0, c_y = 0, c_z = 0;
	float fadeout = 255;

	bool juu_init = false;


};
