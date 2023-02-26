#include "../gm_manager.h"
#include "gm_scene_title.h"
#include "gm_scene_play.h"
#include "gm_scene_tutorial.h"
#include "../model/gm_parts.h"
#include "../../dxlib_ext/dxlib_ext.h"
#include "../gm_camera.h"
#include "../model/gm_airplane.h"
#include "../model/gm_model.h"
#include "gm_scene_result.h"



//--------------------------------------------
//���j���[�I���̏����̎��s
//--------------------------------------------

// ���j���[���ڂ̃N���X
class C_MenuElement
{
public:
	// �R���X�g���N�^
	C_MenuElement(const char* name, int x, int y)
	{
		strcpy(m_name, name);
		m_x = x;
		m_y = y;
	}
	~C_MenuElement() {};
	tnl::Quaternion rot_;
	// �X�V����
	void Update(void)
	{
		GameManager* mgr = GameManager::GetInstance();
		int mouse_x, mouse_y;
		ChangeVolumeSoundMem(160, mgr->juusei);

		GetMousePoint(&mouse_x, &mouse_y);	//�}�E�X�̍��W�擾
		if (m_x < mouse_x && mouse_x < m_x + GetDrawStringWidth(m_name, strlen(m_name)) &&
			m_y < mouse_y && mouse_y < m_y + MENU_STRING_SIZE)	// ������̈��
		{
			if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {	// ������Ă���
				m_state = 2;
				if (m_state == 2 && m_y == 350) {

					mgr->chengeScene(new ScenePlay());
					StopSoundMem(mgr->TitleMusic);
					StopSoundMem(mgr->juudan);
					StopSoundMem(mgr->juusei);

				}
				if (m_state == 2 && m_y == 450) {
					mgr->chengeScene(new SceneResult());
				}

				if (m_state == 2) {
					mgr->juuim = 1;
					if (mgr->juuim == 1) {
						DrawRotaGraph(mgr->x, mgr->y, 2, 0, mgr->juukon, true);
					}
					PlaySoundMem(mgr->juusei, DX_PLAYTYPE_BACK);
					PlaySoundMem(mgr->juudan, DX_PLAYTYPE_BACK);


				}
				if (m_state == 2 && m_y == 550) {
					DxLib_End();
				}

			}
			else													// ������ĂȂ�
				m_state = 1;


			if (m_state == 1) {
				mgr->m_state_c = 1;
			}
			else { mgr->m_state_c = 0; }

		}
		else													// �̈�O
			m_state = 0;
		if (m_state == 0) {
			mgr->c_x = mgr->c_x;
			mgr->c_y = mgr->c_y;
			mgr->c_z = mgr->c_z;
		}
	}

	// �`�揈��
	void Draw(void)
	{
		int string_color;

		switch (m_state)
		{
		case 0:		string_color = MENU_STRING_COLOR_NORMAL;	break;
		case 1:		string_color = MENU_STRING_COLOR_OVER;

			break;
		case 2:		string_color = MENU_STRING_COLOR_CLICK;		break;
		default:	string_color = MENU_STRING_COLOR_ERROR;		break;
		}

		DrawString(m_x, m_y, m_name, string_color);
	}

private:

	char	m_name[128];	// ���ږ��i�[�p�ϐ�
	int		m_x, m_y;		// ���W�i�[�p�ϐ�
	int m_state = 0;        // 0:������� 1:�I���}�E�X 2:�N���b�N���ꂽ
	float box_angle = 0;
};


//-------------------------------------------------
//���j���[�I�𕶎��̕`��
// ------------------------------------------------


class C_Menu
{
public:

	// �R���X�g���N�^
	C_Menu(void)
	{
		const char* menu_name[MENU_NUM] = { "�Q�[���X�^�[�g",  "�w���v",  "�Q�[���I��" };
		const int menu_y[MENU_NUM] = { 350, 450, 550 };

		// ���j���[���ڂ��T�쐬�i�N���X�z�񓮓I�m�ہj
		for (int i = 0; i < MENU_NUM; i++)
			menu_element[i] = new C_MenuElement(menu_name[i], 100 + 30 * i, menu_y[i]);
	}

	// �f�X�g���N�^
	~C_Menu(void)
	{
		// �N���X�z����
		for (int i = 0; i < MENU_NUM; i++)
			delete menu_element[i];
	}

	// �X�V����
	void Update(void)
	{
		for (int i = 0; i < MENU_NUM; i++)
			menu_element[i]->Update();



	}

	// �`�揈��
	void Draw(void)
	{
		for (int i = 0; i < MENU_NUM; i++)
			menu_element[i]->Draw();
	}

private:

	C_MenuElement* menu_element[MENU_NUM];		// ���j���[���ڂ̃N���X�|�C���^
};






void SceneTitle::initialzie() {



	//�[�[�[�[�[�[�^�C�g����ʂ̃Q�[���J���������s�[�[�[�[�[�[
	camera_ = new GmCamera();
	camera_->ctrl = GmCamera::CTRL_TYPE_FREE_LOOK;
	camera_->pos_ = { 0, 0, -300 };

	rot_1 = new Model();




}






void SceneTitle::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();

	// �[�[�[�[�[�[�[BGM�̍Đ��[�[�[�[�[�[�[�[�[
	if (!music) {
		mgr->TitleMusic = LoadSoundMem("sound/desperate.mp3");
		PlaySoundMem(mgr->TitleMusic, DX_PLAYTYPE_NORMAL + DX_PLAYTYPE_LOOP);
		MovieGraphHandle = LoadGraph("movie/tuki.mp4");


		music = true;
	}

	SetMouseDispFlag(FALSE);

	if (!init) {

		mgr->mouse_cursor = LoadGraph("graphics/MouseTitle.png", true);
		mgr->juukon = LoadGraph("graphics/konn.png");
		mgr->juusei = LoadSoundMem("sound/sen_ge_gun12.mp3");
		mgr->juudan = LoadSoundMem("sound/Gun_SE/juudan.mp3");
		init = true;

	}



	GetMousePoint(&mgr->x, &mgr->y);                //�}�E�X�̍��W�擾

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

		StopSoundMem(mgr->TitleMusic);
		mgr->chengeScene(new SceneTutorial());

		SetFontSize(20);
	}
	DrawLineBox(100, 100, 100, 100, BACKGROUND_BLUE);

}




void SceneTitle::render()
{

	//�[�[�[�[�[�[�_�E�����[�h�����t�H���g�̓ǂݍ��݁[�[�[�[�[�[�[�[
	LPCSTR font_path = "./ankokuzonji/Zomzi.TTF";

	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}

	ChangeFont("�Í��]����", DX_CHARSET_DEFAULT);
	GameManager* mgr = GameManager::GetInstance();
	C_Menu menu;


	camera_->update();


	PlayMovieToGraph(MovieGraphHandle);
	DrawExtendGraph(0, 0, 1080, 800, MovieGraphHandle, FALSE);

	// �J�[�\�����킹�ɂ��{�b�N�X�̈ړ�����



	// �X�V�t�F�[�Y 
	menu.Update();

	// �`��t�F�[�Y
	menu.Draw();


	// �J�[�\���ɍ��킹�ē����摜�̕`�揈��

	DrawRotaGraph(mgr->x, mgr->y, 0.2, 0, mgr->mouse_cursor, TRUE);

	SetFontSize(100);
	DrawStringEx(100, 30, RGB(0, 0, 200), "�y World Survaival");
	SetFontSize(50);

}
