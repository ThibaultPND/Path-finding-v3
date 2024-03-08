/***************************************************************
**  Auteur : Thibault Chassagne
**  MAJ : 06/03/2024
*
**  Nom : Path finding
*
*?  Description : Ce logiciel à pour but de crée un simulateur de path finding
*
gcc -o prog -Iinclude -Iinclude/SDL2 src/*.cpp -Llib -lSDL2main -lSDL2 -static -DSDL_MAIN_HANDLED && bin\monProgramme.exe
***************************************************************/
#include <Project.h>
#include <SDL2/SDL.h>
#include "TxUtils.h"
#include "node.h"

int main(int argc, char *argv[])
{
    printf("Debut du programme...\n\n");

    // Initialisation
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        // Erreur init SDL.
    }

    window = SDL_CreateWindow("MonProgramme", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_FENETRE, HAUTEUR_FENETRE, 0);
    if (window == NULL)
    {
        SDL_Quit();
        // Erreur lors de la création de la fenêtre.
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
        // Erreur création du rendu
    }
    srand(SDL_GetTicks());

    SDL_Point mouse = PositionInTheGrid();

    // Initialisation de la grille
    SDL_Point startPoint = {-1, -1}, endPoint = {-1, -1};

    Nodes *open = CreateNodes();
    Nodes *close = CreateNodes();

    renderGrid(startPoint, endPoint, close, open);
    SDL_RenderPresent(renderer);

    // Programme
    SDL_bool programLaunched = SDL_TRUE;
    while (programLaunched)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                programLaunched = SDL_FALSE;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    // Point de départ.
                    startPoint = PositionInTheGrid();
                    printf("Distance = %d ::: %d\n", getDistance(startPoint, endPoint), getDistance(endPoint, startPoint));
                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    // Point d'arrivée.
                    endPoint = PositionInTheGrid();
                }
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_RETURN:
                    if (!PointExist(startPoint) || !PointExist(endPoint))
                    {
                        ErrorBox("Les points de départ et d'arrivé ne sont pas tous défini. \nVeuillez utiliser les boutons de la souris pour les mettre en place");
                        break;
                    }
                    // Lancement de la recherche.
                    SearchSmallestPast(startPoint, endPoint, &close, &open);
                    break;
                case SDLK_BACKSPACE:
                    system("cls");
                    printf("cleared`\n");
                    ClearNodes(&open);
                    PrintNodes(open);
                    ClearNodes(&close);
                    PrintNodes(close);
                    startPoint.x = -1;
                    startPoint.y = -1;
                    endPoint.x = -1;
                    endPoint.y = -1;
                }
                break;
            default:
                break;
            }
        }
        renderGrid(startPoint, endPoint, close, open);
        SDL_RenderPresent(renderer);

        // Limitation du tps du programme à 60.
        SDL_Delay(16);
    }

    // Libération des ressources
    ClearNodes(&open);
    ClearNodes(&close);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    printf("...fin du programme\n");

    return EXIT_SUCCESS;
}