#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include "tools.h"
#include "Tower.h"

// Création d'une tour
Tower* createTower(TowerType type, int posX, int posY, int budget) {
	Tower* newTower = (Tower*) malloc(sizeof(Tower));
	if(newTower == NULL) {
		fprintf(stderr, "Error allocation memory");
        exit(1);
	}

	(*newTower).posX = posX;
	(*newTower).posY = posY;

	(*newTower).type = type;
	if(type == SQUIRTLE) {
		(*newTower).puissance = 500;
		(*newTower).reach = 150;		// Portée de 130 pixels
		(*newTower).cadence = 20;		// Un tir toutes les 2s. (20*1/10 de seconde)
		(*newTower).price = 200;		// Prix de 200€
	}
	else if(type == CHARMANDER) {
		(*newTower).puissance = 400;
		(*newTower).reach = 100;		// Portée de 100 pixels	
		(*newTower).cadence = 8;		// Un tir toutes les 0.8s. (8*1/10 de seconde)
		(*newTower).price = 300;		// Prix de 300€
	}
	else if(type == BULBASAUR) {
		(*newTower).puissance = 200;
		(*newTower).reach = 200;			// Portée de 80 pixels
		(*newTower).cadence = 5;		// Un tir toutes les 0.5s. (5*1/10 de seconde)
		(*newTower).price = 100;		// Prix de 100€
	}
	else if(type == HYBRIDE) {
		(*newTower).puissance = 300;	
		(*newTower).reach = 200;		// Portée de 200 pixels
		(*newTower).cadence = 10;		// Un tir toutes les 1s. (10*1/10 de seconde)
		(*newTower).price = 500;		// Prix de 500€
	}

	(*newTower).next = NULL;

	// Vérification du prix de la tour par rapport au budget
	if(budget >= (*newTower).price) {
		return newTower;
	}
	else {
		return NULL;
	}
}

// Suppression d'une tour
Tower* rmvTower(Tower* t_first, Tower* t) {
	if(t_first == NULL) {
		fprintf(stderr, "pointer is NULL in rmvTower function \n");
		exit(1);
	}

	Tower* root = t_first;
	Tower* t_rmv;

	if(t == t_first) {
		t_rmv = t;
		if((*t_first).next != NULL) {
			t_first = (*t_first).next;
			free(t_rmv);
			return t_first;
		}
		else {
			free(t_rmv);
			return NULL;
		}
	}
	while(t_first != NULL) {
		if((*t_first).next == t) {
			t_rmv = (*t_first).next;
			if((*t_rmv).next != NULL) {
				(*t_first).next = (*t_rmv).next;
			}
			else {
				(*t_first).next = NULL;
				break;
			}
			free(t_rmv);
		}
		t_first = (*t_first).next;
	}

	return root;
}

// Vérification de la validité de l'emplacement de la tour
int checkPosTower(Map map, Tower* t_first, int posX, int posY) {
	// Est-ce que la tour est sur une zone constructible ?
	unsigned char pick_col[3];
	glReadPixels(posX, posY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pick_col);
	if(pick_col[0] != map.buildingAreaColor.r && pick_col[1] != map.buildingAreaColor.g && pick_col[2] != map.buildingAreaColor.b) {
		fprintf(stderr, "zone non constructible\n");
		return 0;
	}

	if(t_first != NULL) {
		Tower* currTower = t_first;
		while(currTower != NULL) {
			// Est-ce que la tour est sur une autre ?
			if(posX >= ((*currTower).posX + 40) || posX <= ((*currTower).posX - 40) || posY >= ((*currTower).posY + 50) || posY <= ((*currTower).posY - 50)) {
				currTower = (*currTower).next;
			}
			else {
				fprintf(stderr, "il y a déjà une tour ici\n");
				return 0;
			}
		}
	}

	return 1;
}

// Détermination du type de tour à construire
TowerType constructTowerType(int posX, int posY) {
	TowerType type = EMPTY;
	// Si clic sur bouton "SQUIRTLE"
	if(posX >= 605 && posX <= 895 && posY >= 217 && posY <= 256) {
		printf("GO SQUIRTLE !\n");
		type = SQUIRTLE;
	}
	// Si clic sur bouton "BULBASAUR"
	if(posX >= 605 && posX <= 895 && posY >= 126 && posY <= 164) {
		printf("GO BULBASAUR !\n");
		type = BULBASAUR;
	}
	// Si clic sur bouton "CHARMANDER"
	if(posX >= 605 && posX <= 895 && posY >= 172 && posY <= 211) {
		printf("CHARMANDER !\n");
		type = CHARMANDER;
	}
	// Si clic sur bouton "HYBRIDE"
	if(posX >= 790 && posX <= 854 && posY >= 12 && posY <= 31) {
		printf("HYBRIDE !\n");
		type = HYBRIDE;
	}

	return type;
}

// Construction (affichage) des tours sur la carte
void constructTower(Tower* t_first) {
	SDL_Surface* tourImg;
	GLuint tourTexture;
	Tower* currTower = t_first;

	while(currTower != NULL) {
		// Chargement de l'image de la tour en fonction de son type
		if((*currTower).type == SQUIRTLE) {
			tourImg = IMG_Load("images/towers/squirtle.png");
		    if(tourImg == NULL) {
		        fprintf(stderr, "impossible de charger l'image squirtle.png \n");
		        exit(1);
		    }
		    tourTexture = loadTexture("images/towers/squirtle.png");
		}
		else if((*currTower).type == CHARMANDER) {
			tourImg = IMG_Load("images/towers/charmander.png");
		    if(tourImg == NULL) {
		        fprintf(stderr, "impossible de charger l'image charmander.png \n");
		        exit(1);
		    }
		    tourTexture = loadTexture("images/towers/charmander.png");		
		}
		else if((*currTower).type == BULBASAUR) {
			tourImg = IMG_Load("images/towers/bulbasaur.png");
		    if(tourImg == NULL) {
		        fprintf(stderr, "impossible de charger l'image bulbasaur.png \n");
		        exit(1);
		    }
		    tourTexture = loadTexture("images/towers/bulbasaur.png");
		}
		
		// Affichage de la texture sur la carte
		glEnable(GL_TEXTURE_2D);
	    glEnable(GL_BLEND);
	    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	    glBindTexture(GL_TEXTURE_2D, tourTexture);
	    
		glBegin(GL_QUADS);
			glColor4ub(255, 255, 255, 255); // Opacité 100%
			glTexCoord2d(0, 0); glVertex2f((*currTower).posX - tourImg->w * 0.5, (*currTower).posY + tourImg->h * 0.5);
			glTexCoord2d(0, 1); glVertex2f((*currTower).posX - tourImg->w * 0.5, (*currTower).posY - tourImg->h * 0.5);
			glTexCoord2d(1, 1); glVertex2f((*currTower).posX + tourImg->w * 0.5, (*currTower).posY - tourImg->h * 0.5);
			glTexCoord2d(1, 0); glVertex2f((*currTower).posX + tourImg->w * 0.5, (*currTower).posY + tourImg->h * 0.5);
		glEnd();
	    
	    glBindTexture(GL_TEXTURE_2D, 0);
	    glDisable(GL_BLEND);
	    glDisable(GL_TEXTURE_2D);

	    currTower = (*currTower).next;
    }

    glDeleteTextures(1, &tourTexture);
    SDL_FreeSurface(tourImg);
}

// Sélection d'une tour construite
Tower* constructTowerSelected(Tower* t_first, int posX, int posY) {
	if(t_first != NULL) {
		Tower* currTower = t_first;
		while(currTower != NULL) {
			// Est-ce que la souris survole une tour ?
			if(posX >= ((*currTower).posX - 30) && posX <= ((*currTower).posX + 30) && posY >= ((*currTower).posY - 30) && posY <= ((*currTower).posY + 30)) {
				return currTower;
			}
			else {
				currTower = (*currTower).next;
			}
		}
	}

	return NULL;
}

// Affichage des caractéristiques de la tour survolée

// Destruction des tours
void destroyTowers(Tower* root) {
	if(root != NULL) {
		destroyTowers(root->next);
		free(root);
	}
}