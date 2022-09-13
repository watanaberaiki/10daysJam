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

	void Update(int stage);

	////�X�e�[�W�̃}�b�v���Z�b�g����
	//void SetMap(int stage);

	////���̏ꏊ�ŃX�e�[�W�����擾����
	//int GetMap(int x,int y, int z);

	void Loding(char const* _FileName);
	//�ǂ̃}�b�v��ǂݍ��ނ����Ǘ�
	void LodingSave(int stage);


	bool mapcol(int x, int y, int z);

	int dist(int x, int y, int z);

public:

	int map[blockY][blockZ][blockX];
	int savemap[blockY][blockZ][blockX];
};