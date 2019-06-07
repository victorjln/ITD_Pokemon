#ifndef ITD_TOWER___
#define ITD_TOWER___

#include "Map.h"
#include "stdlib.h"
#include "stdio.h"

typedef enum {
	SQUIRTLE, BULBASAUR, CHARMANDER, HYBRIDE, EMPTY
}TowerType;

typedef struct tower {
	int posX;
	int posY;
	TowerType type;
	unsigned int puissance;
	unsigned int reach;
	unsigned int cadence;
	int price;
	struct tower* next;
}Tower;

Tower* createTower(TowerType type, int posX, int posY, int budget);
Tower* rmvTower(Tower* t_first, Tower* t);
int checkPosTower(Map map, Tower* t_first, int posX, int posY);
TowerType constructTowerType(int posX, int posY);
void constructTower(Tower* t_first);
Tower* constructTowerSelected(Tower* t_first, int posX, int posY);
void displayTowerFeatures(Tower* t);
void destroyTowers(Tower* root);

#endif