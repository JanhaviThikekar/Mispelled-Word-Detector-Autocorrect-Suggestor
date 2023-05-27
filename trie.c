#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<ctype.h>
#include <stdbool.h>
#include"trie.h"
#define ALPHABET_SIZE (26)
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
#define MAX_FILENAME_LENGTH 100
//#define temp_word 1000
#define MAX_WORD_LENGTH 10000


void progressBar(int progress, int total) 
{
    const int barWidth = 70;

    float ratio = (float)progress / (float)total;
    int barProgress = (int)(ratio * barWidth);

    printf("[");
    for (int i = 0; i < barWidth; i++) {
        if (i < barProgress) {
            printf("=");
        } else if (i == barProgress) {
            printf(">");
        } else {
            printf(" ");
        }
    }
    printf("] %d%%\r", (int)(ratio * 100));
    fflush(stdout);
}


struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = NULL;    
 
    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));    
    if (pNode)     
    {
        int i;
 
        pNode->isLeaf = 0;      
 
        for (i = 0; i < ALPHABET_SIZE; i++)     
            pNode->children[i] = NULL;
    }
 
    return pNode;       //returning pNode
}
 
int count=0;
void insert(struct TrieNode *root, const char *key)         
{
    int level;
    int index;
    int length;
    struct TrieNode *curr = root;

    length  = strlen(key);        
    
    for (level = 0; level < length; level++)        
    {
        index = CHAR_TO_INDEX(key[level]);          
        if (!curr->children[index])
            curr->children[index] = getNode();         
        curr = curr->children[index];           
    }
    
    curr->isLeaf = 1;       
}
 
bool search(struct TrieNode *root, const char *key)         
{
    //initialization of variables
    int level;
    int length ;
    int index;
    struct TrieNode *curr = root;
    
    length = strlen(key);       

    for (level = 0; level < length; level++)         
    {
        index = CHAR_TO_INDEX(key[level]);          
        if (!curr->children[index])                 
            return false;
 
        curr = curr->children[index];              
    }
 
    return (curr != NULL && curr->isLeaf);     
}

void autocorrect_swap(struct TrieNode *root,char word[100])        
{
    int length_word,i,j,k;
    char temp,original[100];
    
    length_word=strlen(word);      
    
    for(i=0;i<length_word;i++)      
        original[i]=word[i];
    
    for(i=0;i<length_word;i++)    
    {
        for(j=i+1;j<length_word;j++)       
        {
            /*swapping logic*/
            temp=word[i];
            word[i]=word[j];
            word[j]=temp;
            if(search(root, word)==1)           
            {
                printf("--> Do you mean %s ?\n",word);  
                count++;
            }
            for(k=0;k<length_word;k++)      
                word[k]=original[k];
        }
    }
}

void autocorrect_repeat(struct TrieNode *root,char word[100])          
{
   
    int i,j,cn=0,length_word;
    char new[101],new1[101];
    
    length_word=strlen(word);          
    
    while(cn<length_word)         
    {
        i=0;

        while(i<=cn)          
        {
            new[i]=word[i];
            i++;
        }
       
        for(j=i-1;i<=length_word;i++,j++)       
        {
            new[i]=word[j];
        }
        for(i=0;i<=length_word;i++)
        {
            new1[i]=new[i];
        }
        new1[length_word+1]=0;      
        if(search(root, new1)==1)           
        {    
            printf("--> Do you mean %s ?\n",new1);
            count++;
        }
        cn++;           
    }
}

void autocorrect_letter(struct TrieNode *root,char word[100])           
{
    int i=0,length_word,j,cn=0;
    char c;
    char new2[100];

    length_word=strlen(word);          
    
    while(cn<length_word)           
    {
            j=0;
            while(j<26)         
            {
                i=0;
                while(i<cn)    
                {
                    new2[i]=word[i];
                    i++;
                }
            
                c = j + 'a';        
                new2[i]=c;      
                i++;
                while(i<length_word)        
                {
                    new2[i]=word[i];
                    i++;
                }
                new2[i]=0;           
                if(search(root, new2)==1)         
                {
                    printf("--> Do you mean %s ?\n",new2);
                    count++;
                }
                j++;    
                
            }
            cn++; 
    } 

}

void autocorrect_hiddenletter(struct TrieNode *root,char word[100])         
{
    
    int length_word,i,cn=0,j,k;
    char c;
    char new3[101],new4[101];
    
    length_word=strlen(word);           
    
    while(cn<length_word)           
    {
        j=0;
        while(j<26)         
        {
            i=0;
            while(i<cn)     
            {
                new3[i]=word[i];
                i++;
            }
            c = j + 'a';       
            new3[i]=c;           
            i++;            
            for(k=i-1;i<=length_word;i++,k++)
            {
                new3[i]=word[k];
            }
            for(i=0;i<=length_word;i++)
            {
                new4[i]=new3[i];
            }
            new4[length_word+1]=0;      
            if(search(root,new4)==1)            
            {
                printf("--> Do you mean %s ?\n",new4);
                count++;
            }
            j++;         
        }
        cn++;        
    }
}

// void findAndReplace(FILE *file, struct TrieNode *root) {
//     char word[MAX_WORD_LENGTH];
//     char replacement[MAX_WORD_LENGTH];
//     char choice;

//     // Read the file word by word
//     while (fscanf(file, "%s", word) != EOF) {
//         // Check if the word is incorrect
//         if (!search(root, word)) {
//             printf("\nIncorrect word found: %s\n", word);
//             printf("Do you want to replace it? (y/n): ");
//             scanf(" %c", &choice);
//             if (tolower(choice) == 'y') {
//                 printf("Enter the replacement word: ");
//                 scanf("%s", replacement);

//                 // Replace the word in the text file
//                 replaceWordInFile(file, word, replacement);

//                 printf("Word replaced successfully!\n");
//             }
//         }
//     }
// }

// void replaceWordInFile(FILE *file, const char *word, const char *replacement) {
//     FILE *fmain = NULL;
//     int choice;
//     int cnt;
//     char *temp_word;
//     char ch[100];
//    // char word[1000];
//     char data[100];
//     char output[][32] = {"incorrect word ", "correct word"};
//     struct TrieNode *root = getNode();
//     int choice1= 0;
//     int count= 0;
//     int totalProgress = 100;
//     fmain = fopen("words.txt", "r");
//     while (fscanf(fmain, "%s", ch) != EOF)
//     {
//         insert(root, ch);
//     }
//     fclose(fmain);
//     char filename[MAX_FILENAME_LENGTH] =  "Aditya.txt";
//     // printf(">> Enter the file name (in txt form): ");
//     // scanf("%s", filename);
//     //FILE *file = fopen(filename, "r");
//     FILE *tempFile;
//     char tempWord[MAX_WORD_LENGTH];

//     // Create a temporary file
//     tempFile = fopen(filename, "w");
//     if (tempFile == NULL) {
//         printf("Error creating temporary file.\n");
//         return;
//     }

//     // Replace the word in the file and write it to the temporary file
//     while (fscanf(file, "%s", tempWord) != EOF) {
//         if (strcmp(tempWord, word) == 0) {
//             fprintf(tempFile, "%s ", replacement);
//         } else {
//             fprintf(tempFile, "%s ", tempWord);
//         }
//     }

//     // Close the files
//     fclose(file);
//     fclose(tempFile);

//     // Replace the original file with the temporary file
//     if (remove(tempFile) != 0) {
//         printf("Error deleting original file.\n");
//         return;
//     }
//     if (rename("temp.txt", filename) != 0) {
//         printf("Error renaming temporary file.\n");
//         return;
//     }

//     // Reopen the original file for further processing
//     file = fopen(filename, "r");
//     if (file == NULL) {
//         printf("Error opening file.\n");
//         return;
//     }
// }