#ifndef TEXTURE_H
#define TEXTURE_H

typedef struct {
	int *pixels;
	int pitch;
} texture;

void setpixel(texture *t, int x, int y, int rgb);
void drawch(texture *t, unsigned char c, int x, int y, int color);
void draws(texture *t, char *s, int len, int x, int y, int color);

#endif
