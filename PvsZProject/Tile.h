#pragma once
#include "GameNode.h"

const int startX = 64;
const int startY = 51;
const int tileWidth = 52;
const int firstMapTileHeight = 63;
const int secondMapTileHeight = 55;

enum class ObstacleType {TOMB, HOLE};
struct SingleTile {
	RECT rc;
	int x;
	int y;
	int tombType;
	bool hasPlant;
	bool hasObstacle;
	bool hasLilypad;
	bool isWater;
};

class Tile : public GameNode {
private:
	Image* _image;

	int _row;
	int _column;
	vector<SingleTile> _vTile;

	int _count;
public:
	HRESULT init(int stageNum);
	void release(void);
	void update(void);
	void render(void);

	int selectTile();
	SingleTile getTile(int index) { return _vTile[index]; }
	RECT getRect(int index) { return _vTile[index].rc; }
	void setPlant(int index, bool plant) { _vTile[index].hasPlant = plant; }
	void setObstacle(int index, bool obstacle) { _vTile[index].hasObstacle = obstacle; }
	void setWater(int index, bool water) { _vTile[index].isWater = water; }
	void setLilypad(int index, bool lilypad) { _vTile[index].hasLilypad = lilypad; }
	POINT getLocation(int index) { return { _vTile[index].x, _vTile[index].y }; }
	int getRow() { return _row; }
	int getColumn() { return _column; }

	void setNightObstacle(int num);
};

