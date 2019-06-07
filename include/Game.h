#ifndef ITD_GAME___
#define ITD_GAME___

typedef struct game {
	int start;
	int pause;
	int help;
	int win;
	int over;
	int budget;
	int nbListsSend; // Nombre de vagues de monstres envoyées
	int nbListsKilled; // Nombre de vagues de monstres éliminées
}Game;

void displayWave(SDL_Surface* figuresIMG, GLuint figures, int wave);
void displayBudget(SDL_Surface* figuresIMG, GLuint figures, int budget);
int posFigure(int i);
void displayFigure(SDL_Surface* figuresIMG, int figure, int posX, int posY);

#endif