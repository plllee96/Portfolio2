#pragma once
#include "GameNode.h"

const int barX = 0;
const int barY = 365;
class Progressbar : public GameNode {
private:
	typedef pair<float, bool> flagInfo;
	typedef vector<flagInfo> vFlagInfo;
	Image* _frameImage;
	Image* _gaugeImage;
	Image* _gaugeHeadImage;
	Image* _flagImage;

	float _maxTime;
	float _startTime;
	float _currentTime;
	vFlagInfo _flagTime;		//Huge-Wave Starting Time

	float _gaugeWidth;

public:
	HRESULT init(float maxTime, vector<float> flagTime);
	void release(void);
	void update(void);
	void render(void);

	bool isHugeWaveTime();
	bool isFinalWave();
	bool isEndWave();
	float getStartTime() { return _startTime; }
};

