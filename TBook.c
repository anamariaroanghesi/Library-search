#include "structuri.h"

TBook *alloc_carte()
{
    TBook *carte = (TBook *)malloc(sizeof(TBook));
    carte->titlu = malloc(LEN_TITLU);
    carte->autor = malloc(LEN_AUTOR);

    return carte;
}

void free_carte(TBook *carte)
{
    free(carte->titlu);
    free(carte->autor);
    free(carte);
}