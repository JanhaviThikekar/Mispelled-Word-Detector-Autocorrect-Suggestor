#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#define ALPHABET_SIZE (26)

struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    int isLeaf;
};

struct TrieNode *getNode(void);
void progressBar(int progress, int total);
void insert(struct TrieNode *root, const char *key);
bool search(struct TrieNode *root, const char *key);        
void autocorrect_swap(struct TrieNode *root,char word[100]);        
void autocorrect_repeat(struct TrieNode *root,char word[100]);          
void autocorrect_letter(struct TrieNode *root,char word[100]);           
void autocorrect_hiddenletter(struct TrieNode *root,char word[100]); 
// void replaceWordInFile(FILE *file, const char *word, const char *replacement);
// void findAndReplace(FILE *file, struct TrieNode *root);
