#pragma once
#include "GameNode.h"
#include "PlantType.h"
#include "PlantManager.h"
#include "ZombieManager.h"
#include "Inventory.h"
#include "Deck.h"
#include "Sun.h"
#include "Tile.h"

enum class GameStatus {SETTING, PLAY, PAUSE, CLEAR};
enum class CursorSelect {NONE, PLANT, SHOVEL};

class GameScene : public GameNode {
private:
	//Image
	Image* _background;

	//Game Controller
	int _stageNum;
	GameStatus _status;
	CursorSelect _cursor;
	RECT _camera;

	//Object & Class
	Deck* _deck;
	Inventory* _inventory;
	PlantManager* _pm;
	ZombieManager* _zm;
	Tile* _tile;

	vector<Sun*> _vSun;
	vector<Sun*>::iterator _viSun;

	//Game Variable
	PlantType _selectedPlant;
	int _selectedPlantIndex;

	int _sun;
	float _sunCount;
	float _sunCooltime;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//set, load
	void setStageNum(int stageNum) { _stageNum = stageNum; }
	void loadStage();

	//play game
	void playGame();
	void mouseControl();
	void sunControl();

	//render
	void printSelectedPlant();

	//debug
	string printPlantType(PlantType type);
};

