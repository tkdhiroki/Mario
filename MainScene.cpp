#include <DxLib.h>
#include "SceneManager.h"
#include "MainScene.h"
#include <tchar.h>
#include "Input.h"

MainScene::MainScene() : playerX(0), playerY(0)
{
	ChangeUpdateState(&MainScene::BeginUpdateState);
	// �O���t�B�b�N�n���h���̐ݒ�
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
	// player�`��
	DrawGraph(playerX, playerY, playerImage, TRUE);

	// map�`��
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
			// id��mapchip_data�̐����������
			map_chip[i][j].id = mapchip_data[i][j];
			// id�̐���������Map�̎�ނ����߂�
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
// player�̈ړ�
void MainScene::PlayerMove()
{
	int pleft = Input::Instance()->GetKeyLeftArrow();
	int pright = Input::Instance()->GetKeyRightArrow();
	// �L�[�{�[�h�̓��͂�player�̈ړ� 
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
	// �L�[���͂��Ȃ���Ԃ�player��dx���ړ�������
	if (pleft != 1 && pright != 1)
	{
		// �ړ��ʔ���
		if (dx != 0)
		{
			if (dx < 0)
				++dx;
			if (dx > 0)
				--dx;
		}
		// �]�g��player�𓮂���
		playerX += dx;
	}
}
// player�̐i�s������block�����������̏���
// x -> �E�A������������l   y -> ��A���������݂�l
void MainScene::PlayerDontEnter(int x, int y)
{
	int mapX = playerX / 40;
	int mapY = playerY / 40;
	// ���E����
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
	// �㉺����
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
// �㉺���E�̐N����������
void MainScene::DontEnter()
{
	PlayerDontEnter(1, 0);
	PlayerDontEnter(-1, 0);
	PlayerDontEnter(0, 1);
	PlayerDontEnter(0, -1);
}

// Goal���ɃV�[���J��
void MainScene::PlayerEnterGoal()
{
	if (MapKind::GoalFrag == GetChipInfo(playerX / 40, playerY / 40))
	{
		SceneManager::Instance()->ChangeRequest(SceneManager::Goal);
	}
}
// player�̃W�����v
// power -> �W�����v�̍���
void MainScene::PlayerJump(int power)
{

}

void MainScene::MapMove()
{
	// player�̈ʒu������
	int pmapX = playerX / 40;
	// map�̈ʒu���ЂƂÂ�����
	if (pmapX == 8)
	{

	}
	// player�̈ʒu������map�ړ����~�߂�B

}