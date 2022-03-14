#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structuri.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
        return -1;

    char *inputFileName = strdup(argv[1]);
    char *outputFileName = strdup(argv[2]);

    FILE *input = fopen(inputFileName, "rt");
    FILE *output = fopen(outputFileName, "wt");

    char *line = NULL;
    size_t len = 0;

    T1 *carti = make_T1('\0');
    T2 *autori = make_T2('\0');

    while (getline(&line, &len, input) != -1)
    {
        char *command = strtok(line, " ");

        if (strcmp(command, "add_book") == 0)
        {
            TBook *carte = alloc_carte();

            strcpy(carte->titlu, strtok(NULL, ":"));
            strcpy(carte->autor, strtok(NULL, ":"));
            carte->rating = atoi(strtok(NULL, ":"));
            carte->nr_pagini = atoi(strtok(NULL, "\n"));

            if (insert_carte(carti, carte->titlu, carte) == 0)
                insert_autor(autori, carte->autor, carte);
        }

        if (strcmp(command, "search_book") == 0)
        {
            char *titlu = strtok(NULL, "\n");
            
            if (titlu[strlen(titlu) - 1] == '~')
                search_T1_prefix(carti, titlu, output);
            else
                search_T1(carti, titlu, output);
        }

        if (strcmp(command, "list_author") == 0)
        {
            char *autor = strtok(NULL, "\n");

            if (autor[strlen(autor) - 1] == '~')    
                search_T2_prefix(autori, autor, output);
            else
                search_T2(autori, autor, output);   
        }

        if (strcmp(command, "search_by_author") == 0)
        {
            char *autor = strtok(NULL, ":");
            char *titlu = strtok(NULL, "\n");

            if (!titlu)   //doar prefix autor
            {
                autor[strlen(autor) - 1] = '\0';
                search_T2_prefix(autori, autor, output);   
            }
            else //autor si titlu sau prefix titlu
            {
                T1 *books = search_autor(autori, autor);

                if (books != NULL)
                {
                    if (titlu[strlen(titlu) - 1] == '~') //este prefix
                        search_T1_prefix(books, titlu, output);
                    else
                        search_T1(books, titlu, output);
                }
                else
                    fprintf(output, "Autorul %s nu face parte din recomandarile tale.\n", autor);
            }
        }

    }

    free(inputFileName);
    free(outputFileName);
    fclose(input);
    fclose(output);
    free(line);

    return 0;
}