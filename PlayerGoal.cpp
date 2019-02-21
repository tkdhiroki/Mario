#include <DxLib.h>
#include "SceneManager.h"
#include "PlayerGoal.h"
#include "Input.h"

PlayerGoal::PlayerGoal()
{
}
PlayerGoal::~PlayerGoal()
{
}

void PlayerGoal::Update()
{
	int release = Input::Instance()->GetMouseRelease();
	if (release & MOUSE_INPUT_LEFT)
	{
		// �N���b�N���ɃQ�[���I��
		SceneManager::Instance()->ChangeRequest(SceneManager::Exit);
	}
}

void PlayerGoal::Draw()
{
	// �N���A�̕���
	const TCHAR *goalStr = _T("�X�e�[�W�N���A");
	int strWidth = GetDrawStringWidth(goalStr, static_cast<int>(_tcslen(goalStr)));
	int offsetX = ((640) - strWidth) / 2;
	SetFontSize(64);
	SetFontThickness(8);
	DrawString(offsetX, 240, goalStr, GetColor(255, 255, 255));


	const TCHAR *pressMouseStr = _T("�}�E�X���N���b�N���Ă�������");
	int strWidth2 = GetDrawStringWidth(pressMouseStr, static_cast<int>(_tcslen(pressMouseStr)));
	int offsetX2 = ((640) - strWidth2) / 2;
	SetFontSize(16);
	SetFontThickness(4);
	DrawString(offsetX2, 400, pressMouseStr, GetColor(255, 255, 255));
}