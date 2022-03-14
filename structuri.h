#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#define LEN_TITLU 51
#define LEN_AUTOR 41
#define N 69
#define ALFABET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! "

typedef struct 
{
    char* titlu;
    char* autor;
    int rating;
    int nr_pagini;
}TBook;

typedef struct Trie1 
{
    char letter; 
    struct Trie1* children[N];
    int is_leaf;
    TBook* carte;
}T1;

typedef struct Trie2 
{
    char letter; 
    struct Trie2* children[N];
    int is_leaf;
    char* autor;
    T1* books;
}T2;

/* Functii Tbook */
TBook* alloc_carte();
void free_carte(TBook* carte);

int index_letter(char letter); /*  returneaza pozitia in alfabet  */

/* Functii trie1 */
T1* make_T1(char letter); /* initializeaza un nod T1 */
int insert_carte(T1 *root, char *word, TBook* carte);   /* insereaza */
void search_T1(T1 *root, char *word, FILE* output); /* search_book */
void search_T1_prefix(T1 *root, char *word, FILE* output); /* search_book_prefix */
void print_trie(T1 *root, FILE* output);    /* afiseaza cartile din trie1 */
void print_trie_prefix(T1 *root, int* ct, FILE *output);    /* afiseaza cel mult 3 carti din trie1  */

/* Functii trie2 */
T2* make_T2(char letter);   /* initializeaza un nod T2 */
int insert_autor(T2 *root, char *word, TBook* carte);   /* insereaza */
void search_T2(T2 *root, char *word, FILE* output);    /* search_autor */
void search_T2_prefix(T2 *root, char *word, FILE* output);     /* search_autor_prefix */
T1* search_autor(T2 *root, char *word);  /* returneaza trie-ul de carti al autorului */
void print_autori_prefix(T2 *root, int *ct, FILE *output);  /* afiseaza cel mult 3 autori din trie2  */