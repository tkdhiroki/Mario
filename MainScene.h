#pragma once
#include "Scene.h"

class MainScene : public Scene
{
private:
	static const int map_width = 32;	// 2stage���̃}�X
	static const int map_height = 8;
	//player�̈ʒu
	int playerX;	
	int playerY;
	// player�̑��x
	static const int playerS = 6;
	static const int playerSdash = 8;
	// player�̑��x�̗]�g
	int dx;

	typedef void (MainScene:: *UpdateState)();
	UpdateState updateState;

	int mapchip_data[map_height][map_width] =
	{
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,20, 0 },	// 1�s��
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,20, 0 }, // 2�s��
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,20, 0 }, // 3�s��
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,20, 0 }, // 4�s��
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,20, 0 }, // 5�s��
		{ 0, 0, 0,10,10,10, 0, 0, 0, 1, 1, 1, 1, 0, 0,10,10,10,10, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0,20, 0 }, // 6�s��
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,20, 0 }, // 7�s��
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,30,30,30, 1, 1, 1, 1, 1, 1 }, // 8�s��
	};
	

	enum MapKind
	{
		None = 0,
		StageBlock = 1,
		ItemBlock = 10,
		GoalFrag = 20,
		DeathFrag = 30,
		Enemy = 44,
		Player = 99
	};

	struct MapChip
	{
		int id;
		MapKind kind;
		unsigned int position_x;
		unsigned int position_y;
	};

	// �O���t�B�b�N�n���h��
	int stageBlock;		// �����ǂȂǂ̉摜
	int itemBlock;		// �A�C�e���u���b�N�̉摜
	int goalFrag;		// �S�[���t���O�̉摜
	int playerImage;			// �v���C���[�摜

	// static const int widhtglidCnt = 16;	// �P�}�X40x40�̃}�X��16�� 
	// static const int heightglidCnt = 8;	// �P�}�X40x40�̃}�X��16�� 
	MapKind map_Info;	// �}�b�v�̏��
	MapChip map_chip[map_height][map_width];
public:
	MainScene();
	~MainScene();
	void Update();
	void Draw();
private:
	// Map�̎�ނ�Ԃ�
	// �����蔻���S�[���̔���Ɏg��
	MapKind GetChipInfo(int x, int y)
	{
		if (x >= 0 && x < map_width || y >= 0 && y < map_height)
		{
			return map_chip[y][x].kind;
		}
		return MapKind::None;
	}

	void InitMapChip();
	void ChangeUpdateState(UpdateState updateState);
	void BeginUpdateState();
	void PlayerMove();
	void PlayerDontEnter(int x, int y);
	void PlayerEnterGoal();
	void PlayerJump(int power);
	void DontEnter();
	void MapMove();
};