#pragma once
#include "GameNode.h"
class ClearScene : public GameNode {
private:
	Image* _whiteChanger;
	Image* _blackChanger;
	Image* _background;

	vector<string> _vData;
	int _stageNum;
	int _money;

	bool _goingMain;
	bool _goingNextStage;
	int _whiteAlpha;
	int _blackAlpha;

	RECT _mainRc;
	RECT _nextStageRc;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void addReward();
	void sceneChanger();
	void mouseControl();
};

