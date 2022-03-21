#pragma once
#include "GameNode.h"
#include "Bullet.h"

#pragma region BulletType
#include "PeashooterBullet.h"
#pragma endregion

class BulletManager : public GameNode {
private:
	typedef vector<Bullet*> vBullet;
	typedef vector<Bullet*>::iterator viBullet;

	vBullet _vBullet;
	viBullet _viBullet;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void addBullet(BulletType type, int x, int y);
	void removeBullet(viBullet iter);

	void debug() { cout << _vBullet.size() << endl; }
};

