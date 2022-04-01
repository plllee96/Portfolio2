#pragma once
#include "GameNode.h"
#include "NumberImage.h"
#include "ShopItem.h"

struct Money {
	NumberImage* numImage;
	int money;
	float x;
	float y;
};

class ShopScene : public GameNode {
private:
	typedef vector<ShopItem*> vItem;
	typedef vector<ShopItem*>::iterator viItem;

private:
	Image* _background;
	Image* _blackChanger;
	int _blackAlpha;
	bool _goingToGame;

	RECT _nextLevelRc;

	Money _money;
	vItem _vItem;
	viItem _viItem;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void sceneChangerControl();
	void mouseControl();

	void loadShop();
};

