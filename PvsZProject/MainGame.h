#pragma once
#include "GameNode.h"


class MainGame : public GameNode {
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MainGame() {}
	~MainGame() {}
};

