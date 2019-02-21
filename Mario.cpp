#include "DxLib.h"
#include "SceneManager.h"
#include "Input.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetMainWindowText(_T("Mario Game"));	// Window�^�C�g����ύX
	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ɐݒ�
	
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;		// �G���[���N�����璼���ɏI��
	}
	
	//Input�N���X�̃C���X�^���X����
	Input::CreateInstance();

	// �V�[���}�l�[�W���[�̃C���X�^���X����
	SceneManager::CreateInstance();

	// �V�[���؂�ւ�
	//SceneManager::Instance()->ChangeRequest(SceneManager::Title);
	SceneManager::Instance()->ChangeRequest(SceneManager::GameMain);

	while (SceneManager::Instance()->IsExit() == false)
	{
		// ProcessMessage()==0 -> �C�x���g�����������肵�Ă���B-1���ƃv���O�����𑁂߂ɏI��������
		if (ProcessMessage() != 0)
		{
			break;
		}

		// �`����ʂ𗠂ɂ���
		SetDrawScreen(DX_SCREEN_BACK);

		// ��ʂ�������
		ClearDrawScreen();

		Input::Instance()->Update();

		//�v�Z�������s��
		SceneManager::Instance()->Update();

		// �`�揈�����s��
		SceneManager::Instance()->Draw();

		// ����ʂ̓��e��\��ʂɔ��f���܂�
		ScreenFlip();
	}

	// �V�[���}�l�[�W���̃C���X�^���X�j��
	SceneManager::DestroyInstance();

	// Input�N���X�̃C���X�^���X�j��
	Input::DestroyInstance();

	DxLib_End();			// �c�w���C�u�����g�p�̏I������

	return 0;			// �\�t�g�̏I�� 
}
