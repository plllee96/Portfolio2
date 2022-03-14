#pragma once
#include "GameNode.h"
class TileSetting : public GameNode {
private:
	enum SELECTINPUT {WIDTH, HEIGHT};
	SELECTINPUT _input;
	unsigned short _tileX;
	unsigned short _tileY;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	unsigned short getX() { return _tileX; }
	unsigned short getY() { return _tileY; }
};

