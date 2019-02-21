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
	static SceneManager * Instance();	// �V���O���g���@�f�U�C���p�^�[��
	//static SceneManager& Instance() = static SceneManager & Instance()
	void ChangeRequest(SceneName name);	// �V�[���J�ڃ��N�G�X�g
public:
	SceneManager();
	~SceneManager();
	bool IsExit();
	void Update();
	void Draw();
private:
	static SceneManager * instance;
	Scene * currntScene;	// ���݂̃V�[��
	SceneName currntSceneName;	// ���݂̃V�[����
	SceneName requestSceneName;	// �v������V�[��(���̃V�[��)
	void DoChange(SceneName name);	// �V�[���J��
	void SceneDestroy();		// �V�[���j��
};
