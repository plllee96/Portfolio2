#pragma once
#include "GameNode.h"
#include "Plant.h"
#include "Tile.h"

#pragma region PLANTS
#include "Peashooter.h"
#include "Sunflower.h"
#include "Wallnut.h"
#include "CherryBomb.h"
#include "PotatoMine.h"
#include "Chomper.h"
#include "Puffshroom.h"
#include "Sunshroom.h"
#include "Scaredyshroom.h"
#pragma endregion

struct generateTypeContainer {
	bool isGenerate;
	float x;
	float y;
	bool isSmallSun;
	bool isTwin;
};

class PlantManager : public GameNode {
private:
	typedef vector<Plant*> vPlant;
	typedef vector<Plant*>::iterator viPlant;
	vPlant _vPlant;
	viPlant _viPlant;

	Tile* _tile;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void addPlant(PlantType type, POINT location);
	Plant* getPlant(int index) { return _vPlant[index]; }
	void removePlant(int index);
	void removePlant(viPlant iter);

	generateTypeContainer isGeneratePlant();
	void setTileMemory(Tile* tile) { _tile = tile; }
};

