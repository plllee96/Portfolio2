#pragma once
#include "GameNode.h"

class HW3 : public GameNode {
private:
	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	HW3() {}
	~HW3() {}

};