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
		// クリック時にゲーム終了
		SceneManager::Instance()->ChangeRequest(SceneManager::Exit);
	}
}

void PlayerGoal::Draw()
{
	// クリアの文字
	const TCHAR *goalStr = _T("ステージクリア");
	int strWidth = GetDrawStringWidth(goalStr, static_cast<int>(_tcslen(goalStr)));
	int offsetX = ((640) - strWidth) / 2;
	SetFontSize(64);
	SetFontThickness(8);
	DrawString(offsetX, 240, goalStr, GetColor(255, 255, 255));


	const TCHAR *pressMouseStr = _T("マウスをクリックしてください");
	int strWidth2 = GetDrawStringWidth(pressMouseStr, static_cast<int>(_tcslen(pressMouseStr)));
	int offsetX2 = ((640) - strWidth2) / 2;
	SetFontSize(16);
	SetFontThickness(4);
	DrawString(offsetX2, 400, pressMouseStr, GetColor(255, 255, 255));
}