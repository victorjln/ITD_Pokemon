#ifndef ITD_TOOLS___
#define ITD_TOOLS___

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

GLuint loadTexture(char* filename);
void displayImageLeft(SDL_Surface* image, GLuint idTexture);
void displayImageRight(SDL_Surface* image, GLuint idTexture);
void displayImageFull(GLuint idTexture);

#endif