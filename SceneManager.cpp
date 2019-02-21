#include <assert.h>
#include <DxLib.h>
#include "SceneManager.h"
#include "TitleScene.h"
#include "MainScene.h"
#include "PlayerGoal.h"

SceneManager * SceneManager::instance = NULL;

// instanceを初期化する
void SceneManager::CreateInstance()
{
	assert(instance == NULL);
	// 式が真であることを表明する
	// この関数が呼ばれたときinstanceがNULLであることを想定している
	instance = new SceneManager();	// オブジェクト一個分のメモリ確保
}

void SceneManager::DestroyInstance()
{
	assert(instance != NULL);
	delete instance;	// メモリ解放
}

SceneManager * SceneManager::Instance()
{
	assert(instance != NULL);
	return instance;
}

//SceneManager & SceneManager::Instance()
//{
//	assert(instance != NULL);
//	return *instance;
//}

// デフォルトコンストラクタ
// 初期化子を使って初期化
SceneManager::SceneManager()	
	:currntScene(NULL)
	, currntSceneName(Max)
	, requestSceneName(Max)
{
}

SceneManager::~SceneManager()
{
	SceneDestroy();
}

bool SceneManager::IsExit()
{
	if (currntSceneName != requestSceneName)
	{
		DoChange(requestSceneName);	// 要求されたシーンに遷移する
	}

	if (requestSceneName == Exit)
		return true;
	return false;
}

void SceneManager::Update()
{
	if (currntScene != NULL)
	{
		currntScene->Update();
	}
}

void SceneManager::Draw()
{
	if (currntScene != NULL)
	{
		currntScene->Draw();
	}
}

void SceneManager::ChangeRequest(SceneName sceneName)
{
	requestSceneName = sceneName;
}
// 
void SceneManager::DoChange(SceneName sceneName)
{
	SceneDestroy();
	switch (sceneName)
	{
	case Title:
		currntScene = new TitleScene();
		break;
	case GameMain:
		currntScene = new MainScene();
		break;
	case Goal:
		currntScene = new PlayerGoal();
		break;
	default:
		break;
	}
	currntSceneName = sceneName;
}

// 現在のシーンを破棄する
void SceneManager::SceneDestroy()
{
	delete currntScene;
	currntScene = NULL;
}