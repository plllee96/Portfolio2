#pragma once
#include "GameNode.h"
#include "Plant.h"

class PlantManager : public GameNode {
private:
	vector<Plant*> _vPlant;
	vector<Plant*>::iterator _viPlant;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void addPlant(PlantType type, POINT location);
	Plant* getPlant(int index) { return _vPlant[index]; }
};

