#pragma once
#include "GameNode.h"

#define TOPLEFT_X				130
#define TOPLEFT_Y				100
#define TILESIZE					60

struct tagObject {
	Image* image;
	RECT rc;
	POINT centerPos;
	POINT tempPos;
	bool select;
};
class TileObject : public GameNode {
private:
	int _x, _y;
	vector<tagObject> _vObject;
	vector<tagObject>::iterator _viObject;
public:
	HRESULT init(int amount, unsigned short x, unsigned short y);
	void release(void);
	void update(void);
	void render(void);
};

