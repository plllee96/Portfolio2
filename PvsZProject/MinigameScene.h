#pragma once
#include "GameNode.h"
#include "PlantType.h"
#include "PlantManager.h"
#include "ZombieManager.h"


class MinigameScene : public GameNode {
private:
	Image* _background;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

