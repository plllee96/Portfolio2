#pragma once
#include "GameNode.h"

class Inventory : public GameNode {
private:
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

