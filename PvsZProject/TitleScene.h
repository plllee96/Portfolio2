#pragma once
#include "GameNode.h"
#include "LetterImage.h"

#define MAX_LENGTH	100
struct firstData {
	int stage;
	int slot;
	int money;
	vector<int> inventory;
};
class TitleScene : public GameNode {
private:
	LetterImage* _userNameImage;
	Image* _image;
	Image* _buttonImage;
	Image* _sceneChanger;
	int _sceneAlpha;
	bool _sceneChange;

	char _text[32];
	firstData _firstData;
	RECT _camera;

	POINT _buttonPosition;
	float _waitCount;

	DWORD _nameLength;
	CHAR _userName[MAX_LENGTH];
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void initFirstData();
};

