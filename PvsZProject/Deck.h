#pragma once
#include "GameNode.h"
#include "Card.h"

class Deck : public GameNode {
private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

