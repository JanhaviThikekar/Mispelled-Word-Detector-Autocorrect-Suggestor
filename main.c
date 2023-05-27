#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include "trie.h"
#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
#define ALPHABET_SIZE (26)
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
#define MAX_FILENAME_LENGTH 100
#define MAX_WORD_LENGTH 10000000



int main()
{
    
    void progressbar();
    void loadprogressbar();

    FILE *fmain = NULL;
    int choice;
    int cnt;
    char *temp_word;
    char ch[100];
    char word[1000];
    char data[100];
    char output[][32] = {"incorrect word ", "correct word"};
    struct TrieNode *root = getNode();
    int choice1= 0;
    int count= 0;
    int totalProgress = 100;

    printf("Loading...\n");
    for (int progress = 0; progress <= totalProgress; progress++)
    {
        progressBar(progress, totalProgress);
        usleep(100000); // Sleep for 100 milliseconds (adjust as needed)
    }
    printf("\n\n\n");
    printf(">> Project By : Aditya Raul(142203016), Rutuja Ingale(142203008), and Janhavi Thikekar(142203009) \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
    printf("\t\t||=================================================================================||\n");
    printf("\t\t||             WELCOME TO MIS-SPELLED DETECTOR AND AUTOCORRECT SUGGESTER           ||\n");
    printf("\t\t||=================================================================================||\n\n");

    fmain = fopen("words.txt", "r");
    while (fscanf(fmain, "%s", ch) != EOF)
    {
        insert(root, ch);
    }
    fclose(fmain);
    char filename[MAX_FILENAME_LENGTH] ;
    printf(">> Enter the file name (in .txt form): ");
    scanf("%s", filename);
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("\n");
        printf(" ____________________________________________________\n");
        printf("|               Error opening the file               |\n");
        printf("|____________________________________________________|\n");
        exit(0);
    }
    else
    {
        printf("\n");
        printf(" ___________________________________________________\n");
        printf("|               File Sucessfully Accepted           |\n");
        printf("|___________________________________________________|\n");  
    }
    do {
    printf("\n\n");
    printf("\n\t\t1. Find Incorrect And Autocorrect Suggestion\n");
    printf("\n\t\t2. Add Word in File\n");
    printf("\n\t\t3. Find and Replace Incorrect Words\n");
    printf("\n\t\t4. Exit\n");
    printf("\n\n>> Enter your choice: ");
    scanf("%d", &choice);
    printf("\n");
    printf("\n\n Your choice is : %d\n\n ",choice);   
    // switch (choice)
    // {
    // case 1:
    // {
    //     printf("You are inside the case 1 ");
    // //FILE *file = fopen(filename, "r");
    // while (fscanf(file, "%[^\n]", word) != EOF) 
    // {
    //     FILE *file = fopen(filename, "r");
    //         temp_word = strtok (word," ,.-\n");
    //         printf("\n");
    //     while ( temp_word != NULL)           
    //     {
    //     // FILE *file = fopen(filename, "r");
    //     // temp_word = strtok (word," ,.-\n");
    //     // printf("\n");
    //     // while ( temp_word != NULL)           
    //     // {
    //         char string1[] = "incorrect word ";
    //         if(strcmp(output[search(root , temp_word)],string1)==0)
    //         {
    //             printf("%s is incorrect\n",temp_word);
    //         }
    //         // printf ("%s is %s\n", temp_word , output[search(root, temp_word)] );
    //         if(search(root, temp_word)==0)           
    //         {
    //             for(cnt=0;cnt<=3;cnt++)
    //             {
    //                 if(cnt==0)
    //                     autocorrect_swap(root,temp_word);
    //                 else if(cnt==1)
    //                     autocorrect_hiddenletter(root,temp_word);
    //                 else if(cnt==2)
    //                     autocorrect_repeat(root,temp_word);
    //                 else 
    //                     autocorrect_letter(root,temp_word);        
    //             }
    //             printf("\n");
    //             if(count==0)
    //             {
    //             printf("\t ________________________________________________________\n");
    //             printf("\t|           Suggestion of a word not found !!            |\n");
    //             printf("\t|________________________________________________________|\n\n");
    //             }
    //             count++;
    //         }    
    //         temp_word = strtok (NULL, " ,.-");
    //     }    
    //      fclose(fmain);
    // }break;}
    switch (choice) {
case 1: {
    printf("You are inside case 1\n");
    fmain = fopen("words.txt", "r");
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        break;
    }

    char temp_word[100]; // Assuming a maximum word length of 100 characters

    while (fscanf(file, "%s", temp_word) != EOF) {
        char string1[] = "incorrect word ";
        if (strcmp(output[search(root, temp_word)], string1) == 0) {
            printf("%s is incorrect\n", temp_word);
        }

        if (search(root, temp_word) == 0) {
            for (cnt = 0; cnt <= 3; cnt++) {
                if (cnt == 0)
                    autocorrect_swap(root, temp_word);
                else if (cnt == 1)
                    autocorrect_hiddenletter(root, temp_word);
                else if (cnt == 2)
                    autocorrect_repeat(root, temp_word);
                else
                    autocorrect_letter(root, temp_word);
            }

            printf("\n");

            if (count == 0) {
                printf("\t ________________________________________________________\n");
                printf("\t|           Suggestion of the word not found !!            |\n");
                printf("\t|________________________________________________________|\n\n");
            }
            count++;
        }
    }

    fclose(file);
    break;
}

    // Other case statements...

   
    case 2:
    {
    FILE *file = fopen(filename, "r");
    while (fscanf(file, "%[^\n]", word) != EOF) 
    {
        temp_word = strtok (word," ,.-\n");
        printf("\n");
        while ( temp_word != NULL)           
        {
            printf("\nDo you want to add any word in our list ('1' for yes '0' for no): ");
            scanf("%d",&choice1); 
            switch(choice1)          
            {
            case 1 :
            {
                printf("\nGive the word which you want to add into list : ");
                scanf("%s",data);       
                if(search(root,data)==0)
                {
                fmain = fopen("words.txt" , "a");            
                fputs(data , fmain);                         
                fputs("\n" , fmain);   
                printf("\n");
                printf(" ___________________________________________________________\n");
                printf("|           Your word is successfully entered !!            |\n");
                printf("|___________________________________________________________|\n");                    
                fclose(fmain);
                //fclose(file);
                }
                else
                {
                printf("\n");
                printf(" ____________________________________________\n");
                printf("|              Word already exists !!         |\n");
                printf("|____________________________________________|\n");    
                printf("\nWord already exists !!\n\n");
                }
                //fclose(fmain);
            }
            break ;
            
            case 0:
            {
            printf("\n");
            printf("\n\n");
            printf("\t||=========================================================================||\n") ;
            printf("\t||                          THANKS FOR VISITING                             ||\n");
            printf("\t||=========================================================================||\n");
            printf("\nProject Guide: Prof. Ashwini Matange\n");
            printf("\n\n\n");  

            fclose(fmain); 
                    }  
                    break;         
                }
                break;
            }
            break;
        }
        break;
    }
    break;
    
    case 3:
        {
            // FILE *file = fopen(filename, "r");
            // findAndReplace( file, root);
            break;
        }
        case 4:
        {
            printf("\n");
            printf("\n\n");
            printf("\t||=========================================================================||\n");
            printf("\t||                          THANKS FOR VISITING                            ||\n");
            printf("\t||=========================================================================||\n");
            printf("\nProject Guide: Prof. Ashwini Matange\n");
            printf("\n\n\n");
            exit(0);
        }
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}

