#include <assert.h>
#include <DxLib.h>
#include "SceneManager.h"
#include "TitleScene.h"
#include "MainScene.h"
#include "PlayerGoal.h"

SceneManager * SceneManager::instance = NULL;

// instance������������
void SceneManager::CreateInstance()
{
	assert(instance == NULL);
	// �����^�ł��邱�Ƃ�\������
	// ���̊֐����Ă΂ꂽ�Ƃ�instance��NULL�ł��邱�Ƃ�z�肵�Ă���
	instance = new SceneManager();	// �I�u�W�F�N�g����̃������m��
}

void SceneManager::DestroyInstance()
{
	assert(instance != NULL);
	delete instance;	// ���������
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

// �f�t�H���g�R���X�g���N�^
// �������q���g���ď�����
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
		DoChange(requestSceneName);	// �v�����ꂽ�V�[���ɑJ�ڂ���
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

// ���݂̃V�[����j������
void SceneManager::SceneDestroy()
{
	delete currntScene;
	currntScene = NULL;
}