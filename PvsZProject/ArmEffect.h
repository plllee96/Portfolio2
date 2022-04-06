#pragma once
#include "GameNode.h"
class ArmEffect : public GameNode {
private:
	Image* _image;
	float _firstY;
	float _x, _y;
	bool _isActive;
public:
	HRESULT init(void);
	virtual HRESULT init(const char* imageName, int x, int y);
	void release(void);
	void update(void);
	void render(void);

	bool getIsActive(void) { return _isActive; }

	ArmEffect() {}
	~ArmEffect() {}
};

