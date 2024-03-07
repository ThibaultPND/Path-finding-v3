#include "Project.h"
#include "TxUtils.h"

SDL_Texture *LoadTexture(const char *path)
{
    SDL_Surface *imageSurface = NULL;
    SDL_Texture *imageTexture = NULL;

    imageSurface = SDL_LoadBMP(path);
    if (imageSurface == NULL)
    {
        // Surface error.
    }
    imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if (imageTexture == NULL)
    {
        // Texture error.
    }
    SDL_FreeSurface(imageSurface);

    return imageTexture;
}

SDL_Texture *LoadingTextureAndRect(const char *path, SDL_Rect rect, Uint16 x, Uint16 y)
{
    SDL_Surface *imageSurface = NULL;
    SDL_Texture *imageTexture = NULL;

    imageSurface = SDL_LoadBMP(path);
    if (imageSurface == NULL)
    {
        // ERROR
    }
    imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if (imageTexture == NULL)
    {
        // ERROR
    }
    SDL_FreeSurface(imageSurface);

    rect.x = x;
    rect.y = y;
    if (SDL_QueryTexture(imageTexture, NULL, NULL, &rect.w, &rect.h))
        // ERROR

        return imageTexture;
}