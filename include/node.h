#if !defined(__NODE_H__)
#define __NODE_H__

typedef struct
{
    int gCost; // Current to start.
    int hCost; // Current to end.
    int fCost; // g + h costs.
} t_Costs;

typedef struct Nodes
{
    t_Costs costs;
    SDL_Point position;

    struct Nodes *origin;
    struct Nodes *prev;
    struct Nodes *next;
} Nodes;

Nodes *CreateNodes();
void PrintNodes(Nodes *nodes);
void AddNode(Nodes **nodes, t_Costs costs, SDL_Point position);
void RemoveNode(Nodes **nodes, Nodes *nodeToRemove);

t_Costs getCosts(SDL_Point start, SDL_Point current, SDL_Point end);
void ClearNodes(Nodes *nodes);

#endif // __NODE_H__
