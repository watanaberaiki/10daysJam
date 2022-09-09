#include "Map.h"
#include <cassert>

bool Map::mapcol(int x, int y, int z)
{
	int mapx = x / (blockScale * blockSize);
	int mapy = y / (blockScale * blockSize);
	int mapz = z / (blockScale * blockSize);

	//���肦�Ȃ��l��false�ŕԂ�
	if (mapx < 0 || mapx >= blockX)	return false;
	if (mapy < 0 || mapy >= blockY)	return false;
	if (mapz < 0 || mapz >= blockZ)	return false;

	return Map::map[mapy][mapz][mapx] == BLOCK;
}

void Map::Initialize() {
}

void Map::Loding(char const* _FileName)
{
	FILE* fp = NULL;

	fopen_s(&fp, _FileName, "r");

	//�z��p�̕ϐ�
	int i, j, k;
	i = 0; j = 0; k = 0;
	//���
	while (i < blockY && j < blockZ && k < blockX) {
		fscanf_s(fp, "%d,", &map[i][j][k]);
		if (k < blockX - 1)
		{
			k++;
		}
		else if (j < blockZ - 1)
		{
			k = 0;
			j++;
		}
		else
		{
			k = 0;
			j = 0;
			i++;
		}
	}


	fclose(fp);
}

void Map::LodingSave(char const* _FileName)
{
	FILE* fp = NULL;

	fopen_s(&fp, _FileName, "r");

	//�z��p�̕ϐ�
	int i, j, k;
	i = 0; j = 0; k = 0;
	//���
	while (i < blockY && j < blockZ && k < blockX) {
		fscanf_s(fp, "%d,", &savemap[i][j][k]);
		if (k < blockX - 1)
		{
			k++;
		}
		else if (j < blockZ - 1)
		{
			k = 0;
			j++;
		}
		else
		{
			k = 0;
			j = 0;
			i++;
		}
	}


	fclose(fp);
}

void Map::Update() {

}

//void Map::SetMap(int stage) {
//
//	for (int i = 0; i < blockY; i++)
//	{
//		for (int j = 0; j < blockZ; j++)
//		{
//			for (int k = 0; k < blockX; k++) 
//			{
//				map[i][j][k] = startMap[i][j][k];
//			}
//		}
//	}
//
//}
//
//int Map::GetMap(int x,int y,int z) {
//	return startMap[y][z][x];
//}

//int Map::dist(int y, int z, int x) {
//
//	return map[y][z][x];
//
//}
