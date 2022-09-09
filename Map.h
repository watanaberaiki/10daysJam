#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <array>
#include <d3dx12.h>
#include <unordered_map>
#include <wrl.h>

//�u���b�N�̃T�C�Y �ύX�s��
const float blockSize = 2.0;
//�u���b�N�̃T�C�Y �ύX��
const float blockScale = 1.0;

//xyz�̃u���b�N�̐�
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

	////�X�e�[�W�̃}�b�v���Z�b�g����
	//void SetMap(int stage);

	////���̏ꏊ�ŃX�e�[�W�����擾����
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