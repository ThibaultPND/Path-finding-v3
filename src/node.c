#include "Project.h"
#include "node.h"

// Prototype
int getDistance(SDL_Point start, SDL_Point end);

// Function
Nodes *CreateNodes()
{
    return NULL;
}

void PrintNodes(Nodes *nodes)
{
    Nodes *current = nodes;
    while (current != NULL)
    {
        printf("[%d]=>", current->costs.fCost);
        current = current->next;
    }
    puts("NULL");
    puts("================");
}

void AddNode(Nodes **nodes, t_Costs costs, SDL_Point position)
{
    Nodes *newNode = (Nodes *)malloc(sizeof(Nodes));
    if (newNode == NULL)
    {
        fprintf(stderr, "Erreur d'allocation !\n");
        exit(EXIT_FAILURE);
    }
    newNode->costs = costs;
    newNode->prev = NULL;
    newNode->position = position;
    if (*nodes == NULL)
    {
        newNode->next = NULL;
    }
    else
    {
        newNode->next = *nodes;
        (*nodes)->prev = newNode;
    }
    *nodes = newNode;
}
void RemoveNode(Nodes **nodes, Nodes *nodeToRemove)
{
    if (*nodes == NULL || nodeToRemove == NULL)
    {
        return;
    }

    if (nodeToRemove == *nodes)
    {
        *nodes = nodeToRemove->next;
    }
    else
    {
        nodeToRemove->prev->next = nodeToRemove->next;
    }

    if (nodeToRemove->next != NULL)
    {
        nodeToRemove->next->prev == nodeToRemove->prev;
    }
    free(nodeToRemove);
}
void ClearNodes(Nodes *nodes)
{
    Nodes *current = nodes;
    Nodes *next = NULL;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

t_Costs getCosts(SDL_Point start, SDL_Point current, SDL_Point end)
{
    t_Costs costs = {
        .gCost = getDistance(current, start),
        .hCost = getDistance(current, end)};

    costs.fCost = costs.gCost + costs.hCost;
    return costs;
}

int getDistance(SDL_Point start, SDL_Point end)
{
    int sum = 0;
    SDL_Point data = {
        .x = abs(start.x - end.x),
        .y = abs(start.y - end.y)};

    while (data.x > 0 || data.y > 0)
    {
        if (data.x > 0 && data.y > 0)
        {
            data.x--;
            data.y--;
            sum += 14;
        }
        else if (data.x > 0)
        {
            data.x--;
            sum += 10;
        }
        else if (data.y > 0)
        {
            data.y--;
            sum += 10;
        }
    }
    return sum;
}