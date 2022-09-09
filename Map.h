#pragma once

//ブロックのサイズ 変更不可
const float blockSize = 2.0;
//ブロックのサイズ 変更可
const float blockScale = 1.0;

//xyzのブロックの数
const int blockX = 10;
const int blockY = 2;
const int blockZ = 10;

enum mapdate
{
	BLUNK,
	BLOCK,
	START
};

class Map
{
public:

	void Initialize();

	void Update();

	//ステージのマップをセットする
	void SetMap();

	//他の場所でステージ情報を取得する
	void GetMap();

public:

	int map[blockY][blockZ][blockX] = {};

};

bool mapcol(int x, int y, int z);

static int startMap[blockY][blockZ][blockX]
{
	{
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,0,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1}
	},
	{
		{2,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,1,1,1,1,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0}
	},
};