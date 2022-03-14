#pragma once

#define A_BULMAX	30
#define B_BULMAX	30
#define PLAYERA_SPEED 5
#define PLAYERB_SPEED 5


struct tagPlayerA {
	RECT rc;
	bool die;
	int health;
	bool confuse;
	int confuseTimer;
};
struct tagBulletA {
	RECT rc;
	bool fire = false;
};
struct tagPlayerB {
	RECT rc;
	bool die;
	int health;

	bool castTimeRewind;
	RECT prevRc;
	int prevHealth;
	int rewindTimer;
};
struct tagBulletB {
	RECT rc;
	POINT homingpos;
	bool fire = false;
	bool homing = false;
};
struct Hook {
	RECT hookhead;
	RECT hookline;
	bool pull;
	bool casting;
	bool grab;
};
struct Shield {
	POINT castpos;
	RECT rc;
	bool casting;
	int health;
};

struct Prism {
	RECT rc;
	bool casting;
	int timer;
};

struct ConfuseBullet {
	RECT rc;
	bool fire;
};

class HomeWork {
private:
	tagBulletA _bulletA[A_BULMAX];
	tagBulletB _bulletB[B_BULMAX];
	tagPlayerA _playerA;
	tagPlayerB _playerB;

	Hook _hook;
	Shield _shield;
	Prism _prism;
	ConfuseBullet _cBullet;

	RECT _stopTimeEffect;
	RECT _maxhealthA;
	RECT _maxhealthB;
	RECT _healthA;
	RECT _healthB;

	int AinvTime;
	int BinvTime;

	bool stopTime;
	int stopTime_timer;

public:
	HomeWork() {}
	~HomeWork() {}

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void movePlayerA();
	void movePlayerB();

	void fireA();
	void fireB();

	void castHook();
	void Hook();

	void castShield();
	void Shield();

	void castStopTime();
	void StopTime();

	void castPrism();
	void Prism();
	
	void castTimeRewind();
	void TimeRewind();

	void castConfuse();
	void ConfuseShot();

	bool RectInRect(RECT rc1, RECT rc2);
};
