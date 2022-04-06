#pragma once
#include "Effect.h"
#include "ArmEffect.h"
#include "ObjectEffect.h"

class EffectManager : public GameNode {
private:
	typedef vector<Effect*> vEffect;
	typedef vector<Effect*>::iterator viEffect;

	typedef vector<ArmEffect*> vArmEffect;
	typedef vector<ArmEffect*>::iterator viArmEffect;

	typedef vector<ObjectEffect*> vObjectEffect;
	typedef vector<ObjectEffect*>::iterator viObjectEffect;

private:
	vEffect _vEffect;
	viEffect _viEffect;

	vArmEffect _vArmEffect;
	viArmEffect _viArmEffect;

	vObjectEffect _vObjectEffect;
	viObjectEffect _viObjectEffect;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void createEffect(const char* fileName, float delay, int x, int y);
	void createArm(const char* fileName, int x, int y);
	void createObject(const char* fileName, int x, int y);
	EffectManager() {}
	~EffectManager() {}
};

