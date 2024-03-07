#ifndef __PROJECT_H__
#define __PROJECT_H__

// Inclusions
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

// Macro dimensions fenêtre
#define HAUTEUR_FENETRE 800
#define LARGEUR_FENETRE 800
#define GRID_SIZE 80
#define TILE_SIZE 10

extern SDL_Renderer *renderer;
extern SDL_Window *window;

void renderGrid(SDL_Point, SDL_Point); // 80x80
SDL_Point PositionInTheGrid();
SDL_bool PointExist(SDL_Point point);

void ErrorBox(const char *message);

#endif // __PROJECT_H__