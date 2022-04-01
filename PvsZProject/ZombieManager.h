#pragma once
#include "GameNode.h"
#include "Zombie.h"

#pragma region ZOMBIES
#include "NormalZombie.h"
#include "CornheadZombie.h"
#include "BucketheadZombie.h"
#include "TubeZombie.h"
#pragma endregion

class ZombieManager : public GameNode {
private:
	typedef vector<Zombie*> vZombie;
	typedef vector<Zombie*>::iterator viZombie;

	vZombie _vZombie;
	viZombie _viZombie;

	int _stageNum;
	int _tileHeight;

	POINT _lastZombiePosition;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void addZombie(ZombieType type, int line);
	void addZombie(int line, int x);
	Zombie* getZombie(int index) { return _vZombie[index]; }
	void removeZombie(int index);
	void removeZombie(viZombie iter);
	void setStage(int stageNum);
	int getZombieAmount() { return _vZombie.size(); }
	POINT getLastZombiePosition() { return _lastZombiePosition; }
};

