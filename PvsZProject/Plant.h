#pragma once
#include "GameNode.h"
#include "PlantType.h"

class Plant : public GameNode {
private:
	Image* _image;
	PlantType _type;
	POINT _location;
	RECT _rc;
public:
	HRESULT init(PlantType type, POINT location);
	void release(void);
	void update(void);
	void render(void);

	virtual void act();
};

