#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_TRIES 6

void printHangman(int mistakes)
{
    printf("\n  +---+\n");
    printf("  |   %c\n", (mistakes >= 1) ? '|' : ' ');
    printf("  |   %c\n", (mistakes >= 2) ? 'O' : ' ');
    printf("  |  %c%c%c\n", (mistakes >= 4) ? '/' : ' ', (mistakes >= 3) ? '|' : ' ', (mistakes >= 5) ? '\\' : ' ');
    printf("  |  %c %c\n", (mistakes >= 6) ? '/' : ' ', (mistakes >= 6) ? '\\' : ' ');
    printf("  |\n");
    printf("=========\n");
}

int main()
{
    FILE* pf = fopen("words.txt", "r");
    if(pf == NULL)
    {
        printf("The file could't open.\n");
        return -1;
    }
    char words[100][50];
    char hints[100][100];
    int count = 0;
    char line[200];
    while(fgets(line, sizeof(line), pf) != NULL)
    {

        int len = strlen(line);
        if(len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';

        char *token = strtok(line, ";");
        strcpy(words[count], token);

        token = strtok(NULL, "\n");
        strcpy(hints[count], token);

        count++;
    }


    fclose(pf);
    printf("Welcome to Hangman! \n");
    srand(time(NULL));
    int randomIndex = rand() % count;

    char secretWord[50];
    strcpy(secretWord, words[randomIndex]);

    for(int i = 0; secretWord[i]; i++)
        secretWord[i] = tolower(secretWord[i]);

    printf("Hint: %s\n", hints[randomIndex]);

    int length = strlen(secretWord);
    char guessedWord[length + 1];
    for(int i = 0 ; i < length; i++)
        guessedWord[i] = '_';

    guessedWord[length] = '\0';

    int mistakes = 0;
    int letterUsed[26] = {};

    while(strcmp(guessedWord, secretWord) != 0 && mistakes < MAX_TRIES)
    {
        printHangman(mistakes);
        printf("\n%s\n", guessedWord);
        printf("You have %d tries left\n", MAX_TRIES - mistakes);

        char input[100];
        char letter;
        scanf(" %s", input);
        if(strlen(input) > 1)
        {
            printf("You can introduce only one letter at a time! \n");
            continue;
        }
        letter = tolower(input[0]);

        if(letterUsed[letter - 'a'] == 1)
        {
            printf("You've already used this letter, try another one! \n");
            continue;
        }

        int found = 0;
        int multipleLetters = 0;

        for (int i = 0; i < length; i++)
        {

            if(secretWord[i] == letter)
            {
                guessedWord[i] = letter;
                found = 1;
                multipleLetters++;
                if(multipleLetters == 1)
                    printf("Good guess! \n");
            }

        }

        if(found == 0)
        {

            mistakes++;
            printf("Try another letter! \n");
        }
        letterUsed[letter - 'a'] = 1;
    }


    if(strcmp(guessedWord, secretWord) == 0)
        printf("\nCongratulations, you won! The word was: %s\n", secretWord);
    else
    {
        printf("\nYou lost! The word was: %s\n", secretWord);
        printHangman(6);
    }
    return 0;
}
