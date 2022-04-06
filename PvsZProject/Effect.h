#pragma once
#include "GameNode.h"
class Effect : public GameNode {
private:

public:
	Image* _image;
	int _currentFrameX;
	int _currentFrameY;

	float _x, _y;
	float _count;	
	float _delay;			
	bool _isActive;	

	HRESULT init(void);
	virtual HRESULT init(const char* imageName, float delay , int x, int y);
	void release(void);
	void update(void);
	void render(void);

	void updateFrame();

	bool getIsActive(void) { return _isActive; }

	Effect(void);
	virtual~Effect(void);
};

