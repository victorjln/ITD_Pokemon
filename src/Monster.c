#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "Node.h"
#include "tools.h"
#include "Monster.h"

int countMonsters(Monster* root) {
	int cpt = 1;
	while((*root).next != NULL) {
		cpt++;
		root = (*root).next;
	}
	return cpt;
}
Monster* createMonster(MonsterType type, int posX, int posY, Node* nextNode, int nbLists) {
	if(nextNode == NULL) {
		fprintf(stderr, "pointer is NULL in createMonster function \n");
		exit(1);
	}

	Monster* newMonster = (Monster*)malloc(sizeof(Monster));
	if(newMonster == NULL) {
		fprintf(stderr, "Error allocation memory \n");
		exit(1);
	}

	if(type == BOUTIN) {
		(*newMonster).life = 40;
		(*newMonster).initialLife = 40;
		(*newMonster).resistance = 5;
		(*newMonster).move = 1;
		(*newMonster).speedDelay = 1;
	}
	else if(type == BARJOT) {
		(*newMonster).life = 80;
		(*newMonster).initialLife = 80;
		(*newMonster).resistance = 10;
		(*newMonster).move = 0;
		(*newMonster).speedDelay = 0;
	}
	else {
		fprintf(stderr, "Unknown monster type \n");
		exit(1);
	}
	// Augmenter la résistance en fonction du nombre de listes envoyées
	(*newMonster).resistance += 10*nbLists;
	(*newMonster).type = type;
	(*newMonster).posX = posX;
	(*newMonster).posY = posY;
	(*newMonster).nextNode = nextNode;
	(*newMonster).next = NULL;

	return newMonster;
}
MonsterList* createMonsterList() {
	MonsterList* newList = (MonsterList*)malloc(sizeof(MonsterList));
	if(newList == NULL) {
		fprintf(stderr, "Error allocation memory \n");
		exit(1);
	}
	(*newList).root = NULL;
	(*newList).nbMonsters = 0;

	return newList;
}
Monster* addMonster(Monster* monsterList, Monster* addMonster) {
	if(monsterList == NULL || addMonster == NULL) {
		fprintf(stderr, "pointer is NULL in addMonster function \n");
		exit(1);
	}	

	(*addMonster).next = monsterList;

	return addMonster;
}
Monster* rmvMonster(Monster* monsterList, Monster* monster) {
	if(monsterList == NULL) {
		fprintf(stderr, "pointer is NULL in rmvMonster function \n");
		exit(1);
	}

	Monster* root = monsterList;
	Monster* rmvMonster;

	// Si le monstre à supprimer est le premier de la liste
	if(monsterList == monster) {
		rmvMonster = monsterList;
		if((*monsterList).next != NULL) { 
			monsterList = (*monsterList).next;
			free(rmvMonster);
			return monsterList;
		}
		else {
			free(rmvMonster);
			return NULL;
		}
	}
	while((*monsterList).next != NULL) {
		if((*monsterList).next == monster) {
			rmvMonster = (*monsterList).next;
			if((*rmvMonster).next != NULL) {
				(*monsterList).next = (*rmvMonster).next;
			}
			else {
				(*monsterList).next = NULL;
				break;
			}
			free(rmvMonster);
		}
		monsterList = (*monsterList).next;
	}

	return root;
}
void rmvMonsterList(MonsterLists* lists, int index) {
	int i = 0;
	for(i = 0; i < (*lists).nbLists-1; i++) {
		if(i >= index) {
			(*lists).lists[i] = (*lists).lists[i+1]; 
		}
	}
	(*lists).nbLists -= 1;
}
int drawMonsters(MonsterLists lists) {
	SDL_Surface* boutin = IMG_Load("images/monsters/boutin.png");
	if(boutin == NULL) {
		fprintf(stderr, "impossible de charger l'image boutin.png \n");
		exit(1);
	}
	SDL_Surface* barjot = IMG_Load("images/monsters/barjot.png");
	if(barjot == NULL) {
		fprintf(stderr, "impossible de charger l'image barjot.png \n");
		exit(1);
	}
	GLuint textureBoutin = loadTexture("images/monsters/boutin.png");
	GLuint textureBarjot = loadTexture("images/monsters/barjot.png");

	Monster* monster;
	int success = 1;
	int i = 0;
	for(i = 0; i < lists.nbLists; i++) {
		monster = lists.lists[i]->root;
		while(monster != NULL) {
			if((*monster).type == BARJOT) {
				if(drawMonster(monster, barjot, textureBarjot) == 0) {
					success = 0;
				}
			}
			else {
				if(drawMonster(monster, boutin, textureBoutin) == 0) {
					success = 0;
				}
			}
			monster = (*monster).next;
		}
	}

	SDL_FreeSurface(boutin);
	SDL_FreeSurface(barjot);

	return success;
}
int drawMonster(Monster* monster, SDL_Surface* boutin, GLuint texture) {
	if(monster->nextNode != NULL) {
		if(monster->move == monster->speedDelay) {
			// Déplacement horizontal du monstre
			if(monster->nextNode->y == monster->posY) {
				// Vers la droite
				if(monster->nextNode->x > monster->posX) {
					monster->posX += 1;
				}
				// Vers la gauche
				else {
					monster->posX -= 1;
				}   
			}
			// Déplacement vertical du monstre
			else {
				// Vers le bas
				if(monster->nextNode->y > monster->posY) {
					monster->posY += 1;
				}
				// Vers le haut
				else {
					monster->posY -= 1;
				}
			}
			if(monster->posX == monster->nextNode->x && monster->posY == monster->nextNode->y) {
				monster->nextNode = monster->nextNode->next;
			}

			monster->move = 0;
		}
		else {
			monster->move += 1;
		}

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, texture);

		glBegin(GL_QUADS);
		glColor3ub(255, 255, 255); // couleur neutre
		glTexCoord2d(0, 1); glVertex2d(monster->posX - boutin->w * 0.5, 600 - monster->posY - boutin->h * 0.5);
		glTexCoord2d(0, 0); glVertex2d(monster->posX - boutin->w * 0.5, 600 - monster->posY + boutin->h * 0.5);
		glTexCoord2d(1, 0); glVertex2d(monster->posX + boutin->w * 0.5, 600 - monster->posY + boutin->h * 0.5);
		glTexCoord2d(1, 1); glVertex2d(monster->posX + boutin->w * 0.5, 600 - monster->posY - boutin->h * 0.5);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);

		// Jauge de vie
		glBegin(GL_QUADS);
		glColor3ub(255, 0, 0);
		glVertex2d(monster->posX, 600 - monster->posY + 45);
		glVertex2d(monster->posX, 600 - monster->posY + 38);
		if(monster->life > 0 && monster->life < 1) {
			glVertex2d(monster->posX + 1, 600 - monster->posY + 38);
			glVertex2d(monster->posX + 1, 600 - monster->posY + 45);
		}
		else {
			glVertex2d(monster->posX + monster->life / 2, 600 - monster->posY + 38);
			glVertex2d(monster->posX + monster->life / 2, 600 - monster->posY + 45);
		}	
		glEnd();

		// Contour de la jauge
		glBegin(GL_LINE_LOOP);
		glColor3ub(30, 30, 30);
		glVertex2d(monster->posX, 600 - monster->posY + 45);
		glVertex2d(monster->posX, 600 - monster->posY + 38);
		glVertex2d(monster->posX + monster->initialLife / 2 , 600 - monster->posY + 38);
		glVertex2d(monster->posX + monster->initialLife / 2, 600 - monster->posY + 45);
		glEnd();

		return 1;
	}
	return 0;
}
MonsterToReach* reachTowerMonster(Tower* currTower, MonsterLists monsterLists) {
	if(currTower != NULL) {
		Monster* monsterToKill = NULL;
		MonsterToReach* currMonster = NULL;
		int i;
		for(i = 0; i < monsterLists.nbLists; i++) {
			monsterToKill = monsterLists.lists[i]->root;
			while(monsterToKill != NULL) {
				// Calcul de la distance entre le monstre et la tour
				float distance = sqrt((((*currTower).posX - (*monsterToKill).posX)*((*currTower).posX - (*monsterToKill).posX)) + (((*currTower).posY - (600-(*monsterToKill).posY))*((*currTower).posY - (600-(*monsterToKill).posY))));
				// Si la distance est inférieure ou égale à la portée de la tour
				if(distance <= (*currTower).reach) {
					// Stockage du monstre et de sa distance à la tour dans une liste
					MonsterToReach* new = (MonsterToReach*) malloc(sizeof(MonsterToReach));
					if(new == NULL) {
						fprintf(stderr, "Error memory allocation\n");
						exit(1);
					}
					(*new).distance = distance;
					(*new).monster = monsterToKill;
					(*new).listNum = i;
					(*new).next = currMonster;
					currMonster = new;
				}
				monsterToKill = (*monsterToKill).next;
			}
		}

		return currMonster;

	}
	
	return NULL;
}
void destroyMonsters(Monster* root) {
	if(root != NULL) {
		destroyMonsters(root->next);
		free(root);
	}
}
