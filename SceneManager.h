#pragma once
#include "Scene.h"

class SceneManager
{
public:
	enum SceneName
	{
		Title,
		GameMain,
		Goal,
		Exit,
		Max
	};
	static void CreateInstance();
	static void DestroyInstance();
	static SceneManager * Instance();	// シングルトン　デザインパターン
	//static SceneManager& Instance() = static SceneManager & Instance()
	void ChangeRequest(SceneName name);	// シーン遷移リクエスト
public:
	SceneManager();
	~SceneManager();
	bool IsExit();
	void Update();
	void Draw();
private:
	static SceneManager * instance;
	Scene * currntScene;	// 現在のシーン
	SceneName currntSceneName;	// 現在のシーン名
	SceneName requestSceneName;	// 要求するシーン(次のシーン)
	void DoChange(SceneName name);	// シーン遷移
	void SceneDestroy();		// シーン破棄
};
