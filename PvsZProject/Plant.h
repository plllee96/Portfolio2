#pragma once
#include "GameNode.h"
#include "PlantType.h"
#include "Tile.h"

struct PlantFrame {
	int maxFrameX;
	int currentFrameX;
	int currentFrameY;
	float count;
	float coolTime;
};

class Plant : public GameNode {
protected:
	//Plants Variable
	Image* _image;
	PlantType _type;
	POINT _location;
	RECT _rc;
	RECT _recognizeRc;
	PlantFrame _frame;
	float _hp;

public:
	virtual HRESULT init(PlantType type, POINT location);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void act();
};

