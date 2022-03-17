#pragma once
#include "GameNode.h"
#include "PlantType.h"

class Plant : public GameNode {
protected:
	Image* _image;
	PlantType _type;
	POINT _location;
	RECT _rc;
public:
	virtual HRESULT init(PlantType type, POINT location);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void act();
};

