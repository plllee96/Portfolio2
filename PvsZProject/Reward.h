#pragma once
#include "GameNode.h"

enum class RewardStatus {GENERATE, OBTAIN};
class Reward : public GameNode {
private:
	Image* _image;
	RewardStatus _status;
	int _rewardNum;
	float _x;
	float _y;
	RECT _rc;

	float _targetY;
	float _gravity;
	float _xspeed;

	bool _show;

public:
	HRESULT init(int stageNum);
	void release();
	void update();
	void render();

	bool isShow() { return _show; }
	void spawnReward(bool show, int x, int y);
	RECT getRect() { return _rc; }
	RewardStatus getStatus() { return _status; }
	void setObtain() { _status = RewardStatus::OBTAIN; }
};

