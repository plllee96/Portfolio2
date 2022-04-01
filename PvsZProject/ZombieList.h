#pragma once
#include "GameNode.h"
#include "ZombieType.h"

const float zombieListCool = 0.5f;

struct tagZombieList {
	Image* image;
	ZombieType type;
	int x;
	int y;
	int frameX;
};
class ZombieList : public GameNode {
private:
	vector<tagZombieList> _list;
	RECT* _camera;
	float _zombieListCount;
public:
	HRESULT init(vector<int> list, RECT* camera);
	void release(void);
	void update(void);
	void render(void);
};

