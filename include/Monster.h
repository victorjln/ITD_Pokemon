#ifndef ITD_MONSTER___
#define ITD_MONSTER___

#include "Tower.h"

#define NB_MONSTER_LIST_MAX 20

typedef enum {
	BOUTIN, BARJOT
}MonsterType;

typedef struct monster {
	MonsterType type;
	float initialLife;
	float life;
	unsigned int resistance;
	int move;
	int speedDelay;
	int posX;
	int posY;
	struct monster* next;
	struct node* nextNode;
}Monster;

typedef struct monsterList {
	struct monster* root;
	int nbMonsters; // Nombre actuel de monstres
	int nbMonstersSend; // Nombre de monstre envoyés
}MonsterList;

typedef struct monsterLists {
	MonsterList* lists[NB_MONSTER_LIST_MAX];
	int nbLists;
}MonsterLists;

// Structure liste stockant les monstres à la portée d'une tour 
typedef struct monsterToReach {
	int distance;
	Monster* monster;
	int listNum;
	struct monsterToReach* next;
}MonsterToReach;


int countMonsters(Monster* root);
Monster* createMonster(MonsterType type, int posX, int posY, Node* nextNode, int nbLists);
MonsterList* createMonsterList();
Monster* addMonster(Monster* monsterList, Monster* addMonster);
Monster* rmvMonster(Monster* monsterList, Monster* monster);
void rmvMonsterList(MonsterLists* lists, int index);
int drawMonsters(MonsterLists lists);
int drawMonster(Monster* monster, SDL_Surface* boutin, GLuint texture);
MonsterToReach* reachTowerMonster(Tower* currTower, MonsterLists monsterLists);
void destroyMonsters(Monster* root);

#endif