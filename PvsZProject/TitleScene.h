#pragma once
#include "GameNode.h"

struct firstData {
	int stage;
	int slot;
	int money;
	vector<int> inventory;
};
class TitleScene : public GameNode {
private:
	Image* _image;
	char _text[32];
	firstData _firstData;
	RECT _camera;

	float _waitCount;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void initFirstData();
};

