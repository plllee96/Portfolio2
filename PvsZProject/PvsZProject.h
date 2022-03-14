#pragma once
//슈팅게임

//총알 최대 개수
#define BULLET_MAX 10
#define PLAYER_SPEED 5
#define ENEMY_MAX 80

//Bullet Manage
struct tagBullet {
	RECT rc;
	bool fire;
};

//Enemy Manage
struct tagEnemy {
	RECT rc;
	int speed;
	bool die;
};

class Lecture2101 {
private:
	tagBullet _bullet[BULLET_MAX];
	tagEnemy _enemy[ENEMY_MAX];
	RECT _maxhealth;
	RECT _health;
	RECT _rc;
	int _invTime;
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void fire();

	Lecture2101() {}
	~Lecture2101() {}
};

