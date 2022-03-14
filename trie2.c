#include "structuri.h"

int index_letter(char letter)
{
    for (int i = 0; ALFABET[i] != '\0'; i++)
        if (ALFABET[i] == letter)
            return i;
    return -1;
}

T2 *make_T2(char letter)
{
    T2 *node = (T2 *)calloc(1, sizeof(T2));
    for (int i = 0; i < N; i++)
        node->children[i] = NULL;
    node->is_leaf = 0;
    node->letter = letter;
    node->autor = NULL;
    node->books = NULL;

    return node;
}

int insert_autor(T2 *root, char *word, TBook *carte)
{
    T2 *temp = root;

    for (int i = 0; word[i] != '\0'; i++)
    {
        int idx = index_letter(word[i]);
        if (temp->children[idx] == NULL)
        {
            temp->children[idx] = make_T2(word[i]);
        }

        temp = temp->children[idx];
    }
    if (temp->is_leaf == 1)
    {
        insert_carte(temp->books, carte->titlu, carte);
        return 1;
    }
    else
    {
        temp->is_leaf = 1;
        temp->books = make_T1('\0');
        temp->autor = malloc(LEN_AUTOR);
        strcpy(temp->autor, word);
        insert_carte(temp->books, carte->titlu, carte);
        return 0;
    }
}

void search_T2(T2 *root, char *word, FILE* output)     
{
    T2 *temp = root;

    for (int i = 0; word[i] != '\0'; i++)
    {
        int position = index_letter(word[i]);
        if (temp->children[position] == NULL){
            fprintf(output, "Autorul %s nu face parte din recomandarile tale.\n", word);
            return ;
        }
        temp = temp->children[position];
    }

    if (temp->is_leaf == 1)
        print_trie(temp->books, output);
    else
        fprintf(output, "Autorul %s nu face parte din recomandarile tale.\n", word);
    
}

void search_T2_prefix(T2 *root, char *word, FILE* output)  
{
    T2 *temp = root;

    for (int i = 0; word[i] != '\0' && word[i] != '~'; i++)
    {
        int position = index_letter(word[i]);
        if (temp->children[position] == NULL)
        {
            fprintf(output, "Niciun autor gasit.\n");
            return ;
        }
        temp = temp->children[position];
    }
    
    {
        int ct = 0;
        print_autori_prefix(temp, &ct, output);
        if (ct == 0)
            fprintf(output, "Niciun autor gasit.\n");
    }

}

T1* search_autor(T2 *root, char *word)     /* search_autor */
{
    T2 *temp = root;

    for (int i = 0; word[i] != '\0'; i++)
    {
        int position = index_letter(word[i]);
        if (temp->children[position] == NULL)
            return NULL;

        temp = temp->children[position];
    }

    if (temp->is_leaf == 1)
        return temp->books;
    
    return NULL;
}

void print_autori_prefix(T2 *root, int *ct, FILE *output)
{
    if (!root)
        return;
    T2 *temp = root;

    if (temp->is_leaf == 1)
    {
        fprintf(output, "%s\n", temp->autor);
        (*ct)++;
    }

    for (int i = 0; i < N; i++)
        if (*ct < 3)
            print_autori_prefix(temp->children[i], ct, output);
}
