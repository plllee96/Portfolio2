#pragma once
#include "GameNode.h"
#include "Plant.h"

#pragma region PLANTS
#include "Peashooter.h"
#include "Sunflower.h"
#pragma endregion

class PlantManager : public GameNode {
private:
	typedef vector<Plant*> vPlant;
	typedef vector<Plant*>::iterator viPlant;
	vPlant _vPlant;
	viPlant _viPlant;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void addPlant(PlantType type, POINT location);
	Plant* getPlant(int index) { return _vPlant[index]; }
	void removePlant(int index);
	void removePlant(viPlant iter);
};

