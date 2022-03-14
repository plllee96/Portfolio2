#pragma once
#include "GameNode.h"

class HW4 : public GameNode {
private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	HW4() {}
	~HW4() {}
};

