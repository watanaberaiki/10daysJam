#include "Map.h"
#include <cassert>

bool mapcol(int x, int y, int z)
{
	int mapx = x / (blockScale * blockSize);
	int mapy = y / (blockScale * blockSize);
	int mapz = z / (blockScale * blockSize);

	//���肦�Ȃ��l��false�ŕԂ�
	if (mapx < 0 || mapx >= blockX)	return false;
	if (mapy < 0 || mapy >= blockY)	return false;
	if (mapz < 0 || mapz >= blockZ)	return false;

	return startMap[mapy][mapz][mapx] == BLOCK;
}

void Map::Initialize() {
	SetMap();
}

void Map::Update() {

}

void Map::SetMap() {

	for (int i = 0; i < blockY; i++)
	{
		for (int j = 0; j < blockZ; j++)
		{
			for (int k = 0; k < blockX; k++) {
				map[i][j][k] = startMap[i][j][k];
			}
		}
	}

}

//void Map::GetMap(int mapx[]) {
//
//
//
//}