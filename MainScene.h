#pragma once
#include "Scene.h"

class MainScene : public Scene
{
private:
	static const int map_width = 32;	// 2stage分のマス
	static const int map_height = 8;
	//playerの位置
	int playerX;	
	int playerY;
	// playerの速度
	static const int playerS = 6;
	static const int playerSdash = 8;
	// playerの速度の余波
	int dx;

	typedef void (MainScene:: *UpdateState)();
	UpdateState updateState;

	int mapchip_data[map_height][map_width] =
	{
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,20, 0 },	// 1行目
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,20, 0 }, // 2行目
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,20, 0 }, // 3行目
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,20, 0 }, // 4行目
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,20, 0 }, // 5行目
		{ 0, 0, 0,10,10,10, 0, 0, 0, 1, 1, 1, 1, 0, 0,10,10,10,10, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0,20, 0 }, // 6行目
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,20, 0 }, // 7行目
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,30,30,30, 1, 1, 1, 1, 1, 1 }, // 8行目
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

	// グラフィックハンドル
	int stageBlock;		// 足場や壁などの画像
	int itemBlock;		// アイテムブロックの画像
	int goalFrag;		// ゴールフラグの画像
	int playerImage;			// プレイヤー画像

	// static const int widhtglidCnt = 16;	// １マス40x40のマスが16こ 
	// static const int heightglidCnt = 8;	// １マス40x40のマスが16こ 
	MapKind map_Info;	// マップの情報
	MapChip map_chip[map_height][map_width];
public:
	MainScene();
	~MainScene();
	void Update();
	void Draw();
private:
	// Mapの種類を返す
	// 当たり判定やゴールの判定に使う
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