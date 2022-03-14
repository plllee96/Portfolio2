#pragma once
#include "GameNode.h"
#include "TileSetting.h"
#include "TileMap.h"

class Tile : public GameNode {
private:
	enum TILEMENU {SETTING, MAP};
	TILEMENU _tilemenu;
	TileSetting* _tileSetting;
	TileMap* _tileMap;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Tile() {}
	~Tile() {}
};

