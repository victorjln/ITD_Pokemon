#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "tools.h"
#include "Game.h"

// Affichage du nombre de vagues
void displayWave(SDL_Surface* figuresIMG, GLuint figures, int wave) {
	glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, figures);

		int posX = 0;
		int i = 1;
		int figure = wave/i%10;
		while(i <= 10) {
			// Détermination de la position du chiffre
			posX = posFigure(i*10000);
			
			// Détermination du chiffre à afficher
			displayFigure(figuresIMG, figure, posX, 90);

			i *= 10;
			figure = wave/i%10;
		}

		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

// Affichage du budget
void displayBudget(SDL_Surface* figuresIMG, GLuint figures, int budget) {
	glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, figures);

		int posX = 0;
		int i = 1;
		int figure = budget/i%10;
		while(i <= 100000) {
			// Détermination de la position du chiffre
			posX = posFigure(i);
			
			// Détermination du chiffre à afficher
			displayFigure(figuresIMG, figure, posX, 0);

			i *= 10;
			figure = budget/i%10;
		}

		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

// Détermination de la position du chiffre (unité, dizaine, centaine, etc.)
int posFigure(int i) {
	int pos = 0;
	switch(i) {
		case 1:
			pos = 190;
			break;
		case 10:
			pos = 170;
			break;
		case 100:
			pos = 150;
			break;
		case 1000:
			pos = 130;
			break;
		case 10000:
			pos = 110;
			break;
		case 100000:
			pos = 90;
			break;
		default:
			break;
	}
	return pos;
}

// Détermination du chiffre à afficher
void displayFigure(SDL_Surface* figuresIMG, int figure, int posX, int posY) {
	switch(figure) {
		case 0:
			glBegin(GL_QUADS);
				glTexCoord2d(0, 0); glVertex2f(posX + 580, posY + 304 + figuresIMG->h * 0.5);
				glTexCoord2d(0, 1); glVertex2f(posX + 580, posY + 304 - figuresIMG->h * 0.5);
				glTexCoord2d(0.1, 1); glVertex2f(posX + 29 + 580, posY + 304 - figuresIMG->h * 0.5);
				glTexCoord2d(0.1, 0); glVertex2f(posX + 29 + 580, posY + 304 + figuresIMG->h * 0.5);
			glEnd();
			break;

		case 1:
			glBegin(GL_QUADS);
				glTexCoord2d(0.1, 0); glVertex2f(posX + 580, posY + 304 + figuresIMG->h * 0.5);
				glTexCoord2d(0.1, 1); glVertex2f(posX + 580, posY + 304 - figuresIMG->h * 0.5);
				glTexCoord2d(0.2, 1); glVertex2f(posX + 29 + 580, posY + 304 - figuresIMG->h * 0.5);
				glTexCoord2d(0.2, 0); glVertex2f(posX + 29 + 580, posY + 304 + figuresIMG->h * 0.5);
			glEnd();
			break;

		case 2:
			glBegin(GL_QUADS);
				glTexCoord2d(0.2, 0); glVertex2f(posX + 580, posY + 304 + figuresIMG->h * 0.5);
				glTexCoord2d(0.2, 1); glVertex2f(posX + 580, posY + 304 - figuresIMG->h * 0.5);
				glTexCoord2d(0.3, 1); glVertex2f(posX + 29 + 580, posY + 304 - figuresIMG->h * 0.5);
				glTexCoord2d(0.3, 0); glVertex2f(posX + 29 + 580, posY + 304 + figuresIMG->h * 0.5);
			glEnd();		
			break;

		case 3:
			glBegin(GL_QUADS);
				glTexCoord2d(0.3, 0); glVertex2f(posX + 580, posY + 304 + figuresIMG->h * 0.5);
				glTexCoord2d(0.3, 1); glVertex2f(posX + 580, posY + 304 - figuresIMG->h * 0.5);
				glTexCoord2d(0.4, 1); glVertex2f(posX + 29 + 580, posY + 304 - figuresIMG->h * 0.5);
				glTexCoord2d(0.4, 0); glVertex2f(posX + 29 + 580, posY + 304 + figuresIMG->h * 0.5);
			glEnd();			
			break;

		case 4:
			glBegin(GL_QUADS);
				glTexCoord2d(0.4, 0); glVertex2f(posX + 580, posY + 304 + figuresIMG->h * 0.5);
				glTexCoord2d(0.4, 1); glVertex2f(posX + 580, posY + 304 - figuresIMG->h * 0.5);
				glTexCoord2d(0.5, 1); glVertex2f(posX + 29 + 580, posY + 304 - figuresIMG->h * 0.5);
				glTexCoord2d(0.5, 0); glVertex2f(posX + 29 + 580, posY + 304 + figuresIMG->h * 0.5);
			glEnd();
			break;

		case 5:
			glBegin(GL_QUADS);
				glTexCoord2d(0.5, 0); glVertex2f(posX + 580, posY + 304 + figuresIMG->h * 0.5);
				glTexCoord2d(0.5, 1); glVertex2f(posX + 580, posY + 304 - figuresIMG->h * 0.5);
				glTexCoord2d(0.6, 1); glVertex2f(posX + 29 + 580, posY + 304 - figuresIMG->h * 0.5);
				glTexCoord2d(0.6, 0); glVertex2f(posX + 29 + 580, posY + 304 + figuresIMG->h * 0.5);
			glEnd();
			break;

		case 6:
			glBegin(GL_QUADS);
				glTexCoord2d(0.6, 0); glVertex2f(posX + 580, posY + 304 + figuresIMG->h * 0.5);
				glTexCoord2d(0.6, 1); glVertex2f(posX + 580, posY + 304 - figuresIMG->h * 0.5);
				glTexCoord2d(0.7, 1); glVertex2f(posX + 29 + 580, posY + 304 - figuresIMG->h * 0.5);
				glTexCoord2d(0.7, 0); glVertex2f(posX + 29 + 580, posY + 304 + figuresIMG->h * 0.5);
			glEnd();
			break;

		case 7:
			glBegin(GL_QUADS);
				glTexCoord2d(0.7, 0); glVertex2f(posX + 580, posY + 304 + figuresIMG->h * 0.5);
				glTexCoord2d(0.7, 1); glVertex2f(posX + 580, posY + 304 - figuresIMG->h * 0.5);
				glTexCoord2d(0.8, 1); glVertex2f(posX + 29 + 580, posY + 304 - figuresIMG->h * 0.5);
				glTexCoord2d(0.8, 0); glVertex2f(posX + 29 + 580, posY + 304 + figuresIMG->h * 0.5);
			glEnd();			
			break;

		case 8:
			glBegin(GL_QUADS);
				glTexCoord2d(0.8, 0); glVertex2f(posX + 580, posY + 304 + figuresIMG->h * 0.5);
				glTexCoord2d(0.8, 1); glVertex2f(posX + 580, posY + 304 - figuresIMG->h * 0.5);
				glTexCoord2d(0.9, 1); glVertex2f(posX + 29 + 580, posY + 304 - figuresIMG->h * 0.5);
				glTexCoord2d(0.9, 0); glVertex2f(posX + 29 + 580, posY + 304 + figuresIMG->h * 0.5);
			glEnd();
			break;

		case 9:
			glBegin(GL_QUADS);
				glTexCoord2d(0.9, 0); glVertex2f(posX + 580, posY + 304 + figuresIMG->h * 0.5);
				glTexCoord2d(0.9, 1); glVertex2f(posX + 580, posY + 304 - figuresIMG->h * 0.5);
				glTexCoord2d(1, 1); glVertex2f(posX + 29 + 580, posY + 304 - figuresIMG->h * 0.5);
				glTexCoord2d(1, 0); glVertex2f(posX + 29 + 580, posY + 304 + figuresIMG->h * 0.5);
			glEnd();
			break;

		default:
			break;
	}
}