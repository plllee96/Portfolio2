#pragma once
#include "GameNode.h"

enum class PlantType {
	PEASHOOTER,
	SUNFLOWER, 
	WALLNUT, 
	CHERRYBOMB,
	POTATOMINE,
	CHOMPER, 

	PUFFSHROOM,
	SUNSHROOM,
	FUMESHROOM,
	SCAREDYSHROOM,
	GRAVEBUSTER,
	DOOMSHROOM,

	LILYPAD,
	SQUASH,
	THREEPEATER,
	CACTUS,
	TORCHWOOD,
	MELONPULT,

	SEASHROOM,
	BLOVER,
	PLANTERN,

	TWINSUNFLOWER
};
enum class CardLocation {DECK, INVENTORY};
class Card : public GameNode {
private:
	PlantType _type;
	CardLocation _location;

	int _price;
	int _coolTime;
	int _maxCoolTime;

public:

};

