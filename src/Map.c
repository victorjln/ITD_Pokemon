#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Map.h"

// Vérification de la validité de la carte itd et création de la map
int createMap(FILE* itd_file, Map* map) {
    int i;
	// Première ligne : @ITD 1
	char code[5];
	int version;
	// Code @ITD
	fgets(code, 5, itd_file);
	if(strcmp(code, "@ITD") != 0) {
		fprintf(stderr, "Error itd file code [@ITD code]\n");
		return 0;
	}
	// Numéro de la version
	fscanf(itd_file, "%d\n", &version);
	if(version < 1) {
		fprintf(stderr, "Error itd file code [version]\n");
       	return 0;
    }
   	
    // Autres lignes du fichier
    char keyword[10];
    int val1 = 0;
    int val2 = 0;
    int val3 = 0;
    // Mot clé "carte"
    fgets(keyword, 7, itd_file);
    if(strcmp(keyword, "carte ") != 0) {
		fprintf(stderr, "Error itd file keyword [carte]\n");
		return 0;
	}
	// Valeur : nom du fichier PPM
    char* filename = (char*) malloc(sizeof(char)*30);
    if(filename == NULL) {
        fprintf(stderr, "Error memory allocation [filename]\n");
    }
    fgets(filename, 30, itd_file);
    //printf("%s", filename);               GERER L'ABSENCE DE POINT !
	char* extension = strchr(filename, '.');
	if(strcmp(extension, ".ppm\n") != 0) {
		fprintf(stderr, "Error itd file keyword value [carte]\n");
       	return 0;
	}
    else {
        (*map).image = filename;
    }

    // Mot clé "chemin"
    fgets(keyword, 8, itd_file);
    if(strcmp(keyword, "chemin ") != 0) {
        fprintf(stderr, "Error itd file keyword [chemin]\n");
        return 0;
    }
    // Couleur chemin
    fscanf(itd_file, "%d %d %d\n", &val1, &val2, &val3);
    if(val1 < 0 || val1 > 255 || val2 < 0 || val2 > 255 || val3 < 0 || val3 > 255) {
        fprintf(stderr, "Error itd file keyword value [chemin]\n");
        return 0;
    }
    else {
        (*map).pathColor = ColorRGB(val1, val2, val3);
    }
    // Mot clé "noeud"
    fgets(keyword, 7, itd_file);
    if(strcmp(keyword, "noeud ") != 0) {
        fprintf(stderr, "Error itd file keyword [noeud]\n");
        return 0;
    }
    // Couleur noeuds
    fscanf(itd_file, "%d %d %d\n", &val1, &val2, &val3);
    if(val1 < 0 || val1 > 255 || val2 < 0 || val2 > 255 || val3 < 0 || val3 > 255) {
        fprintf(stderr, "Error itd file keyword value [noeud]\n");
        return 0;
    }
    else {
        (*map).nodeColor = ColorRGB(val1, val2, val3);
    }
    // Mot clé "construct"
    fgets(keyword, 11, itd_file);
    if(strcmp(keyword, "construct ") != 0) {
        fprintf(stderr, "Error itd file keyword [construct]\n");
        return 0;
    }
    // Couleur zones constructibles
    fscanf(itd_file, "%d %d %d\n", &val1, &val2, &val3);
    if(val1 < 0 || val1 > 255 || val2 < 0 || val2 > 255 || val3 < 0 || val3 > 255) {
        fprintf(stderr, "Error itd file keyword value [construct]\n");
        return 0;
    }
    else {
        (*map).buildingAreaColor = ColorRGB(val1, val2, val3);
    }
    // Mot clé "in"
    fgets(keyword, 4, itd_file);
    if(strcmp(keyword, "in ") != 0) {
        fprintf(stderr, "Error itd file keyword [in]\n");
        return 0;
    }
    // Couleur zone d'entrée
    fscanf(itd_file, "%d %d %d\n", &val1, &val2, &val3);
    if(val1 < 0 || val1 > 255 || val2 < 0 || val2 > 255 || val3 < 0 || val3 > 255) {
        fprintf(stderr, "Error itd file keyword value [in]\n");
        return 0;
    }
    else {
        (*map).inColor = ColorRGB(val1, val2, val3);
    }
     // Mot clé "out"
    fgets(keyword, 5, itd_file);
    if(strcmp(keyword, "out ") != 0) {
        fprintf(stderr, "Error itd file keyword [out]\n");
        return 0;
    }
    // Couleur zone de sortie
    fscanf(itd_file, "%d %d %d\n", &val1, &val2, &val3);
    if(val1 < 0 || val1 > 255 || val2 < 0 || val2 > 255 || val3 < 0 || val3 > 255) {
        fprintf(stderr, "Error itd file keyword value [out]\n");
        return 0;
    }
    else {
        (*map).outColor = ColorRGB(val1, val2, val3);
    }
    // Nombre de noeuds
    fscanf(itd_file, "%d\n", &val1);
    long posFile = ftell(itd_file);
    // Nombre de lignes restantes
    unsigned int nbLines = 1;
    int c;
    while((c = fgetc(itd_file)) != EOF) {
        if(c == '\n') {
            nbLines++;
        }
    }
    if(val1 != nbLines) {
        fprintf(stderr, "Error itd file number of nodes\n");
        return 0;
    }
    else {
        (*map).nbNodes = val1;
    }
    // Vérification de la correspondance des coordonnées de chaque noeud à des pixels de l'image
    // Re-positionnement du curseur de lecture dans le fichier après le nombre de noeuds
    fseek(itd_file, posFile, SEEK_SET);
    // Chargement de l'image pour avoir accès à ses dimensions
    // Suppression du caractère '\n' en trop à la fin du nom du fichier 
    i = 0;
    while(i < strlen(filename)) {
        if(filename[i] == '\n') {
            filename[i] = '\0';
        }
        i++;
    }
    // Chargement de l'image
    char file[256] = "images/";
    strcat(file, filename);
    SDL_Surface* image = IMG_Load(file);
    if(image == NULL) {
        fprintf(stderr, "impossible de charger l'image %s\n", file);
        exit(1);
    }
    // Vérification
    i = 0;
    while(i < nbLines) {
        fscanf(itd_file, "%d %d\n", &val2, &val3);
        if(val2 > image->w || val3 > image->h || val2 < 0 || val3 < 0) {
            fprintf(stderr, "Error itd file node coordinates\n");
            return 0;
        }
        i++;
    }

    // Création de la liste des noeuds
    fseek(itd_file, posFile, SEEK_SET);
    int currX, currY;
    fscanf(itd_file, "%d %d\n", &currX, &currY);
    Node* currNode = createNode(currX, currY);
    Node* root = currNode;
    for(i = 1; i < nbLines; i++) {
        fscanf(itd_file, "%d %d\n", &val1, &val2);
        Node* node = createNode(val1, val2);
        (*currNode).next = node;
        currNode = (*currNode).next;
    }
    (*currNode).next = NULL;

    (*map).listNodes = root;

    // Destruction des données de l'image chargée
    SDL_FreeSurface(image);

    return 1;
}

// Chargement et ouverture de l'image (IM_1)
Map loadMap(char* itd_fileName) {
    // Ouverture fichier (r: lecture seule)
    FILE* itd_file = fopen(itd_fileName, "r");
    if(itd_file == NULL) {
        // Erreur ouverture fichier
        fprintf(stderr, "Error opening itd file : %s\n", itd_fileName);
        exit(1);
    }
    else {
        Map map;
        // Vérification de la validité du fichier et création de la map
        if(createMap(itd_file, &map)) {
            // Carte valide
            printf("Map créée\n");
            return map;
        }
        else {
            fprintf(stderr, "Invalid itd file : %s\n", itd_fileName);
            exit(1);
        }
    }
}

// Dessin du chemin à partir des coordonnées des noeuds
void drawPath(Node* root) {
    glBegin(GL_LINES);
    while(root->next != NULL) {
        glVertex2d(root->x, 600-root->y);
        glVertex2d(root->next->x, 600-root->next->y);

        root = root->next;
    }
    glEnd();
}
