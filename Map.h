#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <array>
#include <d3dx12.h>
#include <unordered_map>
#include <wrl.h>

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
	PLAYER,
	GOAL,
	CATUP,
	CATLEFT,
	CATDOWN,
	CATRIGHT
};

class Map
{
public:

	void Initialize();

	void Update();

	////ステージのマップをセットする
	//void SetMap(int stage);

	////他の場所でステージ情報を取得する
	//int GetMap(int x,int y, int z);

	void Loding(char const* _FileName);
	void LodingSave(char const* _FileName);


bool mapcol(int x, int y, int z);

int dist(int x,int y,int z);

public:

 int map[blockY][blockZ][blockX];
 int savemap[blockY][blockZ][blockX];

};


//static int startMap[blockY][blockZ][blockX]
//{
//	{
//		{1,1,1,1,1,1,1,1,1,1},
//		{1,1,1,1,1,1,1,1,1,1},
//		{1,1,1,1,1,1,1,1,1,1},
//		{1,1,1,1,1,1,1,1,1,1},
//		{1,1,1,1,1,1,1,1,1,1},
//		{1,1,1,1,1,1,1,1,1,1},
//		{1,1,1,1,1,1,1,1,1,1},
//		{1,1,1,1,1,1,1,0,1,1},
//		{1,1,1,1,1,1,1,1,1,1},
//		{1,1,1,1,1,1,1,1,1,1}
//	},
//	{
//		{2,0,0,0,0,0,0,0,0,0},
//		{0,0,0,0,0,0,0,0,0,0},
//		{0,0,1,1,1,1,1,1,0,0},
//		{0,0,0,0,0,0,0,0,0,0},
//		{0,0,0,0,0,0,0,0,0,0},
//		{0,0,0,0,0,0,0,0,0,0},
//		{1,0,0,0,0,0,0,0,0,0},
//		{0,0,0,0,0,0,0,0,0,0},
//		{0,0,0,0,0,0,0,0,0,0},
//		{0,0,0,0,0,0,0,0,0,0}
//	},
//};