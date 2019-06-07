#include "tools.h"

GLuint loadTexture(char* filename) {
	GLuint textureId;
	GLenum format;

	SDL_Surface* image = IMG_Load(filename);
	if(image == NULL) {
      fprintf(stderr, "impossible de charger l'image %s\n", filename);
      exit(1);
   }

   glGenTextures(1, &textureId);
   glBindTexture(GL_TEXTURE_2D, textureId);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

   	switch(image->format->BytesPerPixel) {
	    case 1:
	    format = GL_RED;
	    break;
	    case 3:
	    format = GL_RGB;
	    break;
	    case 4:
	    format = GL_RGBA;
	    break;
	    default:
	      /* On ne traite pas les autres cas */
	    fprintf(stderr, "Format des pixels de l’image %s non pris en charge\n", filename);
	    exit(1);
 	}

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, format,
    GL_UNSIGNED_BYTE, image->pixels);

   glBindTexture(GL_TEXTURE_2D, 0);
   SDL_FreeSurface(image);

   return textureId;
}
void displayImageRight(SDL_Surface* image, GLuint idTexture) {
	glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, idTexture);

		glBegin(GL_QUADS);
			glColor4ub(255, 255, 255, 255); // Opacité 100%
			glTexCoord2d(0, 0); glVertex2f(600, image->h);
			glTexCoord2d(0, 1); glVertex2f(600, 0);
			glTexCoord2d(1, 1); glVertex2f(image->w + 600, 0);
			glTexCoord2d(1, 0); glVertex2f(image->w + 600, image->h);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}
void displayImageLeft(SDL_Surface* image, GLuint idTexture) {
	glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, idTexture);

		glBegin(GL_QUADS);
			glColor4ub(255, 255, 255, 255); // Opacité 100%
			glTexCoord2d(0, 0); glVertex2f(0, image->h);
			glTexCoord2d(0, 1); glVertex2f(0, 0);
			glTexCoord2d(1, 1); glVertex2f(image->w, 0);
			glTexCoord2d(1, 0); glVertex2f(image->w, image->h);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}
void displayImageFull(GLuint idTexture) {
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, idTexture);
		glBegin(GL_QUADS);
			glColor4ub(255, 255, 255, 255); // Opacité 100%
			glTexCoord2d(0, 0); glVertex2f(0, WINDOW_HEIGHT);
			glTexCoord2d(0, 1); glVertex2f(0, 0);
			glTexCoord2d(1, 1); glVertex2f(WINDOW_WIDTH, 0);
			glTexCoord2d(1, 0); glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT);
		glEnd();
	glDisable(GL_TEXTURE_2D);
}