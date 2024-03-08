#include "Project.h"

SDL_Renderer *renderer = NULL;
SDL_Window *window = NULL;

Nodes *lowestFcost(Nodes *nodes);
Nodes *inNodes(Nodes *nodes, SDL_Point position);
void renderTile(Uint8 r, Uint8 g, Uint8 b, Uint8 x, Uint8 y);

void renderGrid(SDL_Point start, SDL_Point end, Nodes *close, Nodes *open)
{
    // Remise à blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    if (PointExist(start))
        renderTile(0, 0xF5, 0, start.x, start.y);

    if (PointExist(end))
        renderTile(0xF5, 0, 0, end.x, end.y);

    Nodes *current = close;
    while (current != NULL)
    {
        renderTile(0xFF, 0x80, 0, current->position.x, current->position.y);
        current = current->next;
    }
    current = open;
    while (current != NULL)
    {
        renderTile(0xAA, 0xAA, 0, current->position.x, current->position.y);
        current = current->next;
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
void renderTile(Uint8 r, Uint8 g, Uint8 b,
                Uint8 x, Uint8 y)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    SDL_Rect Rect = {
        .x = (x * TILE_SIZE) + 1,
        .y = (y * TILE_SIZE) + 1,
        .w = TILE_SIZE - 1,
        .h = TILE_SIZE - 1};
    SDL_RenderFillRect(renderer, &Rect);
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

void SearchSmallestPast(SDL_Point start, SDL_Point end, Nodes **close, Nodes **open)
{
    system("cls");

    ClearNodes(open);
    ClearNodes(close);
    *open = CreateNodes();
    *close = CreateNodes();

    AddNode(open, getCosts(0, start, start, end), start);

    uint32_t starter = SDL_GetTicks64();
    while (SDL_TRUE)
    {
        Nodes *current = lowestFcost(*open);

        printf("==( open )====\n");
        PrintNodes(*open);
        printf("current = %d (%d:%d)\n", current->costs.fCost, current->position.x, current->position.y);

        RemoveNode(open, current);
        AddNode(close, current->costs, current->position);

        // Chemin trouvé
        if (current->costs.hCost <= 0)
        {
            printf("Chemin trouvé en %d ms\n", SDL_GetTicks64() - starter);
            // Nodes *path = CreateNodes();
            // while (current->origin != current)
            // {
            //     AddNode(&path, current->costs, current->position);
            //     current = current->origin;
            // }
            // PrintNodes(path);

            break;
        }
        Nodes *stmg = current;
        // Pour tout les voisins de current.
        printf("Début itération voisins de current");
        int count = 0;
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                printf("\n\tVoisin actuel {%d:%d}:\n", j, i);
                // Verifier si le noeud actuel est traversable et si il n'est pas fermé.
                SDL_Point neighbourPosition = {
                    .x = current->position.x + j,
                    .y = current->position.y + i};

                printf("position : {%d:%d}\n", neighbourPosition.x, neighbourPosition.y);
                printf("current  : {%d:%d}\n", current->position.x, current->position.y);

                if (!PointExist(neighbourPosition))
                {
                    printf("[-] do not exist > %d:%d\n", neighbourPosition.x, neighbourPosition.y);
                    continue;
                }

                // TODO Verifier si il y a  un mur.
                // <

                if (inNodes(*close, neighbourPosition))
                {
                    printf("[-] close  %d:%d\n", neighbourPosition.x, neighbourPosition.y);
                    continue;
                }

                Nodes *neighbour = inNodes(*open, neighbourPosition);
                if (neighbour == NULL)
                {
                    AddNode(open, getCosts(current->costs.gCost, current->position, neighbourPosition, end), neighbourPosition);
                    neighbour = *open;
                }
                else
                {
                    t_Costs newPath = getCosts(current->costs.gCost, current->position, neighbourPosition, end);
                    if (newPath.fCost < neighbour->costs.fCost)
                    {
                        neighbour->costs = newPath;
                    }
                }
                neighbour->origin = current;
                count++;
            }
        }
        printf("Fin itération sur  les voisins (total : %d)", count);
        if (stmg != current)
        {
            fprintf(stderr, "ALERTE  CURRENT WAS  CHANGED\n");
            exit(1);
        }
    }
    PrintNodes(*open);
}

Nodes *inNodes(Nodes *nodes, SDL_Point position)
{
    Nodes *current = nodes;
    while (current != NULL)
    {
        if (current->position.x == position.x &&
            current->position.y == position.y)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Trouve le noeud avec le fcost le plus bas.
// Si deux noeud sont au minimum on prendra celuis avec le hcost le plus bas.
Nodes *lowestFcost(Nodes *nodes)
{
    if (nodes == NULL)
        return NULL;

    Nodes *current = nodes;
    Nodes *NodeWithLowestFcost = nodes;

    while (current != NULL)
    {
        if ((current->costs.fCost < NodeWithLowestFcost->costs.fCost) ||
            ((current->costs.fCost == NodeWithLowestFcost->costs.fCost) &&
             (current->costs.hCost < NodeWithLowestFcost->costs.hCost)))
        {
            NodeWithLowestFcost = current;
        }
        current = current->next;
    }
    return NodeWithLowestFcost;
}

void ErrorBox(const char *message)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message, NULL);
}