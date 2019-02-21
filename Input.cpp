#include <assert.h>
#include <DxLib.h>

#include "Input.h"

Input * Input::instance = NULL;

void Input::CreateInstance()
{
	assert(instance == NULL);
	instance = new Input();
}

void Input::DestroyInstance()
{
	assert(instance != NULL);
	delete instance;
	instance = NULL;
}

Input * Input::Instance()
{
	assert(instance != NULL);
	return instance;
}

Input::Input()
	:mouseOn(0)
	, mousePress(0)
	, mouseRelease(0)
{
}

Input::~Input()
{
}

void Input::Update()
{
	// マウスの状態取得処理
	int mouse = GetMouseInput();	// マウスの入力状態取得
	int diff_mouse = mouse ^ mouseOn;	// (mouse)^mouseOn べき乗
	this->mousePress = diff_mouse & mouse;	// 論理積　互いが１のとき１
	this->mouseRelease = diff_mouse & this->mouseOn;
	this->mouseOn = mouse;	// 前回のマウスの情報

	// キー入力の状態取得処理
	this->keyLeftArrow = key[KEY_INPUT_LEFT];
	this->keyRightArrow = key[KEY_INPUT_RIGHT];
	this->keySpace = key[KEY_INPUT_SPACE];
}

int Input::GetMouseOn()
{
	return mouseOn;
}
int Input::GetMousePress()
{
	return mousePress;
}
int Input::GetMouseRelease()
{
	return mouseRelease;
}
int Input::GetKeyLeftArrow()
{
	return keyLeftArrow;
}
int Input::GetKeyRightArrow()
{
	return keyRightArrow;
}
int Input::GetKeySpace()
{
	return keySpace;
}