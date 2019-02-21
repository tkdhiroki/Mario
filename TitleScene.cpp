#include <DxLib.h>
#include "SceneManager.h"
#include "TitleScene.h"
#include "Input.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	int release = Input::Instance()->GetMouseRelease();
	if (release & MOUSE_INPUT_LEFT)
	{
		// �N���b�N���ɃQ�[���V�[���Ɉړ�
		SceneManager::Instance()->ChangeRequest(SceneManager::GameMain);
	}
}

void TitleScene::Draw()
{
	// �^�C�g���̕���
	const TCHAR *titleStr = _T("Mario Game");
	// GetDrawStringWidth( char *String , int StrLen ) �`�悵�����̕�����̕������
	// String ���𒲂ׂ���   StrLen ���ׂ���������̒���
	// static_cast<int> ������|�C���^��<int>�^�ɃL���X�g���Ă���
	// _tcslen TCHAR�̍ۂɕ�����擾�p�Ɏg�p
	int strWidth = GetDrawStringWidth(titleStr, static_cast<int>(_tcslen(titleStr)));
	int offsetX = ((640) - strWidth) / 2;
	DrawString(offsetX, 100, titleStr, GetColor(255, 255, 255));

	// �N���b�N����
	const TCHAR *pressMouseStr = _T("�}�E�X���N���b�N���Ă�������");
	int strWidth2 = GetDrawStringWidth(pressMouseStr, static_cast<int>(_tcslen(pressMouseStr)));
	int offsetX2 = ((640) - strWidth2) / 2;
	DrawString(offsetX2, 400, pressMouseStr, GetColor(255, 255, 255));
}
