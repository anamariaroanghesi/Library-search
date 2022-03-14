#include "structuri.h"

T1 *make_T1(char letter)
{
    T1 *node = (T1 *)calloc(1, sizeof(T1));
    for (int i = 0; i < N; i++)
        node->children[i] = NULL;
    node->is_leaf = 0;
    node->letter = letter;
    node->carte = NULL;

    return node;
}

int insert_carte(T1 *root, char *word, TBook *carte)
{
    T1 *temp = root;

    for (int i = 0; word[i] != '\0'; i++)
    {
        int idx = index_letter(word[i]);
        if (temp->children[idx] == NULL)
        {
            temp->children[idx] = make_T1(word[i]);
        }

        temp = temp->children[idx];
    }

    if (temp->is_leaf == 1)
        return 1;
    else
    {
        temp->is_leaf = 1;
        temp->carte = carte;
        return 0;
    }
}

void search_T1(T1 *root, char *word, FILE* output)  /* search_book */
{
    if (!root)
        return ;
    T1 *temp = root;

    for (int i = 0; word[i] != '\0'; i++)
    {
        int position = index_letter(word[i]);
        if (temp->children[position] == NULL){
            fprintf(output, "Cartea %s nu exista in recomandarile tale.\n", word);
            return ;
        }
            
        temp = temp->children[position];
    }
    if (temp->is_leaf == 1)
    {
        TBook *carte = temp->carte;
        fprintf(output, "Informatii recomandare: %s, %s, %d, %d\n", carte->titlu, carte->autor, carte->rating, carte->nr_pagini);
    }
    else
        fprintf(output, "Cartea %s nu exista in recomandarile tale.\n", word);
}

void search_T1_prefix(T1 *root, char *word, FILE *output) /* search_book_prefix */
{
    if (!root)
        return;
    T1 *temp = root;

    for (int i = 0; word[i] != '\0' && word[i] != '~'; i++)
    {
        int position = index_letter(word[i]);
        if (temp->children[position] == NULL)
        {
            fprintf(output, "Nicio carte gasita.\n");
            return;
        }

        temp = temp->children[position];
    }

    int ct = 0;
    print_trie_prefix(temp, &ct, output);
    if (ct == 0)
        fprintf(output, "Nicio carte gasita.\n");
}

void print_trie(T1 *root, FILE *output)
{
    if (!root)
        return;
    T1 *temp = root;

    if (temp->is_leaf == 1)
        fprintf(output, "%s\n", temp->carte->titlu);

    for (int i = 0; i < N; i++)
    {
        print_trie(temp->children[i], output);
    }
}

void print_trie_prefix(T1 *root, int *ct, FILE *output)
{
    if (!root)
        return;
    T1 *temp = root;

    if (temp->is_leaf == 1)
    {
        fprintf(output, "%s\n", temp->carte->titlu);
        (*ct)++;
    }

    for (int i = 0; i < N; i++)
        if (*ct < 3)
            print_trie_prefix(temp->children[i], ct, output);
}

