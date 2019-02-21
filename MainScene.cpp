#include <DxLib.h>
#include "SceneManager.h"
#include "MainScene.h"
#include <tchar.h>
#include "Input.h"

MainScene::MainScene() : playerX(0), playerY(0)
{
	ChangeUpdateState(&MainScene::BeginUpdateState);
	// グラフィックハンドルの設定
	stageBlock = LoadGraph("mario_block.png");
	itemBlock = LoadGraph("mario_block.png");
	goalFrag = LoadGraph("mario_block.png");
	playerImage = LoadGraph("mario_player.png");
}
MainScene::~MainScene()
{
}

void MainScene::Update()
{
	(this->*updateState)();
	PlayerMove();
	DontEnter();
	int space = Input::Instance()->GetKeySpace();
	if (space == 1)
	{
		PlayerJump(100);
	}
}

void MainScene::ChangeUpdateState(UpdateState state)
{
	updateState = state;
}

void MainScene::BeginUpdateState()
{
	InitMapChip();
}

void MainScene::Draw()
{
	// player描画
	DrawGraph(playerX, playerY, playerImage, TRUE);

	// map描画
	for (int y = 0; y < map_height; y++)
	{
		for (int x = (int)(playerX % 10); x < map_width; x++)
		{
			int posx = map_chip[y][x].position_x;
			int posy = map_chip[y][x].position_y;

			switch (map_chip[y][x].kind)
			{
			case MapKind::StageBlock:
				DrawGraph(posx, posy, stageBlock, TRUE);
				break;
			case MapKind::ItemBlock:
				DrawGraph(posx, posy, itemBlock, TRUE);
				break;
			case MapKind::GoalFrag:
				DrawGraph(posx, posy, goalFrag, TRUE);
				break;
			default:
				break;
			}
		}
	}
}

void MainScene::InitMapChip()
{
	for (int i = 0; i < map_height; i++)
	{
		for (int j = 0; j < map_width / 2; i++)
		{
			// idにmapchip_dataの数字をいれる
			map_chip[i][j].id = mapchip_data[i][j];
			// idの数字を見てMapの種類を決める
			switch (map_chip[i][j].id)
			{
			case MapKind::None:
				map_chip[i][j].kind = MapKind::None;
				break;
			case MapKind::StageBlock:
				map_chip[i][j].kind = MapKind::StageBlock;
				break;
			case MapKind::ItemBlock:
				map_chip[i][j].kind = MapKind::ItemBlock;
				break;
			case MapKind::GoalFrag:
				map_chip[i][j].kind = MapKind::GoalFrag;
				break;
			case MapKind::DeathFrag:
				map_chip[i][j].kind = MapKind::DeathFrag;
				break;
			default:
				break;
			}
			map_chip[i][j].position_x = j * 40;
			map_chip[i][j].position_y = i * 40;
		}
	}
}
// playerの移動
void MainScene::PlayerMove()
{
	int pleft = Input::Instance()->GetKeyLeftArrow();
	int pright = Input::Instance()->GetKeyRightArrow();
	// キーボードの入力でplayerの移動 
	if (pright == 1)
	{
		playerX += playerS;
		dx = playerS;
	}

	if (pleft == 1)
	{
		playerX -= playerS;
		dx = -playerS;
	}
	// キー入力がない状態でplayerをdx分移動させる
	if (pleft != 1 && pright != 1)
	{
		// 移動量判定
		if (dx != 0)
		{
			if (dx < 0)
				++dx;
			if (dx > 0)
				--dx;
		}
		// 余波分playerを動かす
		playerX += dx;
	}
}
// playerの進行方向にblockがあった時の処理
// x -> 右、左方向を見る値   y -> 上、下方向をみる値
void MainScene::PlayerDontEnter(int x, int y)
{
	int mapX = playerX / 40;
	int mapY = playerY / 40;
	// 左右方向
	if (x != 0 && y == 0)
	{
		if (MapKind::StageBlock == GetChipInfo(mapX + x, mapY))
		{
			int mapPosX = map_chip[mapY][mapX + x].position_x;
			if (x > 0)
				playerY = mapPosX - 40;
			else
				playerY = mapPosX + 40;
			dx = 0;
		}
	}
	// 上下方向
	else if (y != 0 && x == 0)
	{
		if (MapKind::StageBlock == GetChipInfo(mapX, mapY + y))
		{
			int mapPosY = map_chip[mapY + y][mapX].position_y;
			if (y > 0)
				playerY = mapPosY - 40;
			else
				playerY = mapPosY + 40;

			dx = 0;
		}
	}
}
// 上下左右の侵入区域を見る
void MainScene::DontEnter()
{
	PlayerDontEnter(1, 0);
	PlayerDontEnter(-1, 0);
	PlayerDontEnter(0, 1);
	PlayerDontEnter(0, -1);
}

// Goal時にシーン遷移
void MainScene::PlayerEnterGoal()
{
	if (MapKind::GoalFrag == GetChipInfo(playerX / 40, playerY / 40))
	{
		SceneManager::Instance()->ChangeRequest(SceneManager::Goal);
	}
}
// playerのジャンプ
// power -> ジャンプの高さ
void MainScene::PlayerJump(int power)
{

}

void MainScene::MapMove()
{
	// playerの位置を見る
	int pmapX = playerX / 40;
	// mapの位置をひとつづつ動かす
	if (pmapX == 8)
	{

	}
	// playerの位置を見てmap移動を止める。

}