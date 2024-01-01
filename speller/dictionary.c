// Implements a dictionary's functionality

#define _GNU_SOURCE
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"




// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;
// Func prototypes
void assign(int hashnumb, char *word);
//void recur(node *tab[26 * 26], node *n, int hashnumb);

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
int counter = 0;

// Hash table
node *table[N * N];

FILE *dict;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char lowerword[LENGTH + 1];
    for (int i = 0; i <= LENGTH; i++)
    {
        lowerword[i] = tolower(word[i]);
    }
    int hasher = hash(lowerword);
    if (table[hasher] == NULL)
    {
        return false;
    }
    else
    {
        node *tmp = table[hasher];
        while (tmp != NULL)
        {
            if (strcmp(lowerword, tmp->word) == 0)
            {
                return true;
            }
            else
            {
                tmp = tmp->next;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // apostrophe is letter 27 or pos 26
    // TODO: Improve this hash function
    //printf("%li\n", strlen(word));
    char firstlet;
    int count = 0;
    char secondlet;
    char wordcopy[strlen(word)];
    int imp = strlen(word);
    for (int i = 0; i < strlen(word); i++)
    {
        if (strcmp(&word[i], "\n") != 0)
        {
            wordcopy[i] = word[i];
            count++;
        }
    }
    firstlet = wordcopy[0];

    int hashnumb;
    if (count != 1)
    {
        secondlet = (wordcopy[1]);
    }
    else
    {
        secondlet = firstlet;
    }

    if (imp == 1)
    {
        secondlet = firstlet;
    }

    if (secondlet != '\'' && secondlet != 39)
    {
        hashnumb = (26 * (firstlet - 'a') + (secondlet - 'a'));
    }
    else
    {
        hashnumb = (26 * (firstlet - 'a') + 26);
    }

    return hashnumb;

}
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Initialise some variables
    int buffersize = 50;
    char *buffer = malloc(buffersize * sizeof(char));
    char *freer = buffer;
    size_t length = 0;

    // Load dict file
    dict = fopen(dictionary, "r");
    if (dict != NULL)
    {
        while (getline(&buffer, &length, dict) != -1)
        {
            int hasher = hash(buffer);
            assign(hasher, buffer);
            counter++;

            //char s[LENGTH + 1];
            /*
            for (int j = 0; j <= LENGTH; j++)
            {
                s[j] = table[hasher]->word[j];
            }
            printf("%s\n",s);
            */
        }
        free(freer);
        if (buffer)
        {
            free(buffer);
        }
        fclose(dict);
        return true;
    }

    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{



    return counter;
}


// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < (26 * 26); i++)
    {
        node *list = table[i];
        while (list != NULL)
        {
            node *tmp = list->next;
            free(list);
            list = tmp;
        }
    }
    return true;
}

void assign(int hashnumb, char *word)
{
    // Create a new node
    node *n = malloc(sizeof(node));
    for (int i = 0; i < strlen(word); i++)
    {
        if (strcmp(&word[i], "\n") != 0)
        {
            n->word[i] = word[i];
        }
    }
    n->next = NULL;

    if (n == NULL)
    {
        return;
    }
    if (table[hashnumb] == NULL)
    {
        //table[hashnumb] = malloc(sizeof(node));
        table[hashnumb] = n;
    }
    else
    {
        node *tmp = table[hashnumb];

        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = n;
    }




    //recur(table, n, hashnumb);

}


// assign(table, hashnumb, wordcopy);

/*
void recur(node *tab[26 * 26], node *n, int hashnumb)
{
    if (tab[hashnumb]->next == NULL)
    {
        tab[hashnumb] = n;
    }
    else
    {
        recur(tab[hashnumb]->next, n, hashnumb);
    }

}
*/