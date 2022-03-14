#pragma once
#include "GameNode.h"
#include "TileObject.h"

#define OBJECT_AMOUNT		2

struct tagTile {
	unsigned short x;
	unsigned short y;
	RECT rc;
};

class TileMap : public GameNode {
private:
	unsigned short _x;
	unsigned short _y;
	vector<tagTile> _vTile;
	TileObject* _object;

public:
	HRESULT init(unsigned short x, unsigned short y);
	void release(void);
	void update(void);
	void render(void);
};

