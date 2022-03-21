#pragma once
#include "GameNode.h"
#include "Zombie.h"

#pragma region ZOMBIES
#include "NormalZombie.h"
#pragma endregion

class ZombieManager : public GameNode {
private:
	typedef vector<Zombie*> vZombie;
	typedef vector<Zombie*>::iterator viZombie;

	vZombie _vZombie;
	viZombie _viZombie;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void addZombie(ZombieType type, int line);
	Zombie* getZombie(int index) { return _vZombie[index]; }
	void removeZombie(int index);
	void removeZombie(viZombie iter);
};

