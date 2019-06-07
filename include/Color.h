#ifndef ITD_COLOR___
#define ITD_COLOR___

typedef struct color {
	unsigned int r;
	unsigned int g;
	unsigned int b;
}Color;

Color ColorRGB(unsigned int r, unsigned int g, unsigned int b);

#endif