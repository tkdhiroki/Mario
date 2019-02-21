#include "DxLib.h"
#include "SceneManager.h"
#include "Input.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetMainWindowText(_T("Mario Game"));	// Windowタイトルを変更
	ChangeWindowMode(TRUE); // ウィンドウモードに設定
	
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;		// エラーが起きたら直ちに終了
	}
	
	//Inputクラスのインスタンス生成
	Input::CreateInstance();

	// シーンマネージャーのインスタンス生成
	SceneManager::CreateInstance();

	// シーン切り替え
	//SceneManager::Instance()->ChangeRequest(SceneManager::Title);
	SceneManager::Instance()->ChangeRequest(SceneManager::GameMain);

	while (SceneManager::Instance()->IsExit() == false)
	{
		// ProcessMessage()==0 -> イベント処理を肩代わりしてれるやつ。-1だとプログラムを早めに終了させる
		if (ProcessMessage() != 0)
		{
			break;
		}

		// 描画先画面を裏にする
		SetDrawScreen(DX_SCREEN_BACK);

		// 画面を初期化
		ClearDrawScreen();

		Input::Instance()->Update();

		//計算処理を行う
		SceneManager::Instance()->Update();

		// 描画処理を行う
		SceneManager::Instance()->Draw();

		// 裏画面の内容を表画面に反映します
		ScreenFlip();
	}

	// シーンマネージャのインスタンス破棄
	SceneManager::DestroyInstance();

	// Inputクラスのインスタンス破棄
	Input::DestroyInstance();

	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;			// ソフトの終了 
}
