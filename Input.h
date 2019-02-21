#pragma once

class Input
{
public:
	Input();
	~Input();
	static void CreateInstance();
	static void DestroyInstance();
	static Input * Instance();
	void Update();
	int GetMouseOn();
	int GetMousePress();
	int GetMouseRelease();
	int GetKeyLeftArrow();
	int GetKeyRightArrow();
	int GetKeySpace();
private:
	static Input * instance;
	int mouseOn;
	int mousePress;
	int mouseRelease;
	char key[256];	// キー取得用配列
	int keyLeftArrow;
	int keyRightArrow;
	int keySpace;
};
