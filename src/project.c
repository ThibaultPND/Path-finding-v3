#include "Project.h"

SDL_Renderer *renderer = NULL;
SDL_Window *window = NULL;

void renderGrid(SDL_Point start, SDL_Point end)
{
    // Remise à blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    if (PointExist(start))
    {
        SDL_SetRenderDrawColor(renderer, 0x00, 0xF5, 0x00, SDL_ALPHA_OPAQUE);
        SDL_Rect startRect = {
            .x = (start.x * 10) + 1,
            .y = (start.y * 10) + 1,
            .w = 9,
            .h = 9};
        SDL_RenderFillRect(renderer, &startRect);
    }

    if (PointExist(end))
    {
        SDL_SetRenderDrawColor(renderer, 0xF5, 0x00, 0x00, SDL_ALPHA_OPAQUE);
        SDL_Rect endRect = {
            .x = (end.x * 10) + 1,
            .y = (end.y * 10) + 1,
            .w = 9,
            .h = 9};
        SDL_RenderFillRect(renderer, &endRect);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 0; i < GRID_SIZE; i++)
    {
        SDL_RenderDrawLine( // Horizontal.
            renderer,
            0,
            i * TILE_SIZE,
            GRID_SIZE * TILE_SIZE,
            i * TILE_SIZE);

        SDL_RenderDrawLine( // Vertical.
            renderer,
            i * TILE_SIZE,
            0,
            i * TILE_SIZE,
            GRID_SIZE * TILE_SIZE);
    }
}

// TODO
void renderTile(SDL_Renderer *renderer,
                Uint8 r, Uint8 g, Uint8 b,
                Uint8 a,
                Uint8 x, Uint8 y)
{
    //
}

SDL_Point PositionInTheGrid()
{
    int mouse_x;
    int mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    return (SDL_Point){mouse_x / TILE_SIZE, mouse_y / TILE_SIZE};
}

SDL_bool PointExist(SDL_Point point)
{
    if (point.x >= 0 && point.x < GRID_SIZE &&
        point.y >= 0 && point.y < GRID_SIZE)
    {
        return SDL_TRUE;
    }
    return SDL_FALSE;
}

void ErrorBox(const char *message)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message, NULL);
}