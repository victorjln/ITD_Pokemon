#ifndef ITD_MAP___
#define ITD_MAP___

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Color.h"
#include "Node.h"

typedef struct map {
	char* image; 
	Color pathColor;
	Color nodeColor;
	Color buildingAreaColor;
	Color inColor;
	Color outColor;
	unsigned int nbNodes;
	Node* listNodes;
}Map;

int createMap(FILE* itd_file, Map* map);
Map loadMap(char* itd_fileName);
void drawPath(Node* root);

#endif