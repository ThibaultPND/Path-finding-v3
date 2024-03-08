#ifndef __PROJECT_H__
#define __PROJECT_H__

// Inclusions
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "node.h"

// Macro dimensions fenêtre
#define HAUTEUR_FENETRE 800
#define LARGEUR_FENETRE 800
#define GRID_SIZE 8
#define TILE_SIZE 100

extern SDL_Renderer *renderer;
extern SDL_Window *window;

void renderGrid(SDL_Point start, SDL_Point end, Nodes *close, Nodes *open); // 80x80
SDL_Point PositionInTheGrid();
SDL_bool PointExist(SDL_Point point);

void SearchSmallestPast(SDL_Point start, SDL_Point end, Nodes **close, Nodes **open);

void ErrorBox(const char *message);

#endif // __PROJECT_H__