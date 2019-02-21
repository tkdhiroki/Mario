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
		// クリック時にゲームシーンに移動
		SceneManager::Instance()->ChangeRequest(SceneManager::GameMain);
	}
}

void TitleScene::Draw()
{
	// タイトルの文字
	const TCHAR *titleStr = _T("Mario Game");
	// GetDrawStringWidth( char *String , int StrLen ) 描画した時の文字列の幅を取る
	// String 幅を調べたい   StrLen 調べたい文字列の長さ
	// static_cast<int> 文字列ポインタを<int>型にキャストしている
	// _tcslen TCHARの際に文字列取得用に使用
	int strWidth = GetDrawStringWidth(titleStr, static_cast<int>(_tcslen(titleStr)));
	int offsetX = ((640) - strWidth) / 2;
	DrawString(offsetX, 100, titleStr, GetColor(255, 255, 255));

	// クリック勧告
	const TCHAR *pressMouseStr = _T("マウスをクリックしてください");
	int strWidth2 = GetDrawStringWidth(pressMouseStr, static_cast<int>(_tcslen(pressMouseStr)));
	int offsetX2 = ((640) - strWidth2) / 2;
	DrawString(offsetX2, 400, pressMouseStr, GetColor(255, 255, 255));
}
