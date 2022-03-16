#pragma once
#include "GameNode.h"

class TitleScene : public GameNode {
private:
	char _text[32];
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};
