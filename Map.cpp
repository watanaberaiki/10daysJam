#include "Map.h"

bool mapcol(int x, int y, int z)
{
	int mapx = x / (blockScale * blockSize);
	int mapy = y / (blockScale * blockSize);
	int mapz = z / (blockScale * blockSize);

	//‚ ‚è‚¦‚È‚¢’l‚Ífalse‚Å•Ô‚·
	if (mapx < 0 || mapx >= blockX)	return false;
	if (mapy < 0 || mapy >= blockY)	return false;
	if (mapz < 0 || mapz >= blockZ)	return false;

	return Map[mapy][mapz][mapx] == BLOCK;
}