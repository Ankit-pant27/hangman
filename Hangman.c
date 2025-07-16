#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define MAX_WORDS 100
#define MAX_LENGTH 50
#define MAX_TRIES 6
int loadWords(char words[][MAX_LENGTH]);
void chooseWord(char words[][MAX_LENGTH], int wordCount, char chosenWord[]);
void displayHangman(int tries);
void displayWordState(char word[], int wordLength, int guessed[]);
int isWordGuessed(int guessed[], int length);
int main() {
    char words[MAX_WORDS][MAX_LENGTH];
    char chosenWord[MAX_LENGTH];
    int guessed[MAX_LENGTH] = {0}; 
    int wordCount = loadWords(words);
    if (wordCount == 0) {
        printf("No words loaded. Exiting.\n");
        return 1;
    }
    chooseWord(words, wordCount, chosenWord);
    int length = strlen(chosenWord);
    int tries = 0;
    char guess;
    printf("🎯 Welcome to Hangman!\n");
    while (tries < MAX_TRIES) {
        displayHangman(tries);
        displayWordState(chosenWord, length, guessed);
        printf("\nEnter a letter: ");
        scanf(" %c", &guess);
        guess = tolower(guess);
        int found = 0;
        for (int i = 0; i < length; i++) {
            if (chosenWord[i] == guess && guessed[i] == 0) {
                guessed[i] = 1;
                found = 1;
            }
        }
        if (!found) {
            tries++;
            printf("❌ Wrong guess! Tries left: %d\n", MAX_TRIES - tries);
        }
        if (isWordGuessed(guessed, length)) {
            printf("\n🎉 Congratulations! You guessed the word: %s\n", chosenWord);
            return 0;
        }
    }
    displayHangman(tries);
    printf("\n💀 Game over! The word was: %s\n", chosenWord);
    return 0;
}
int loadWords(char words[][MAX_LENGTH]) {
    FILE *file = fopen("words.txt", "r");
    if (!file) {
        printf("Error opening words file.\n");
        return 0;
    }
    int count = 0;
    while (fgets(words[count], MAX_LENGTH, file)) {
        words[count][strcspn(words[count], "\n")] = '\0';
        count++;
        if (count >= MAX_WORDS)
            break;
    }
    fclose(file);
    return count;
}
void chooseWord(char words[][MAX_LENGTH], int wordCount, char chosenWord[]) {
    srand(time(NULL));
    int index = rand() % wordCount;
    strcpy(chosenWord, words[index]);
}
void displayWordState(char word[], int wordLength, int guessed[]) {
    printf("Word: ");
    for (int i = 0; i < wordLength; i++) {
        if (guessed[i])
            printf("%c ", word[i]);
        else
            printf("_ ");
    }
    printf("\n");
}
int isWordGuessed(int guessed[], int length) {
    for (int i = 0; i < length; i++) {
        if (!guessed[i])
            return 0;
    }
    return 1;
}
void displayHangman(int tries) {
    printf("\n");
    printf(" +---+\n");
    printf(" |   %c\n", tries >= 1 ? 'O' : ' ');
    printf(" |  %c%c%c\n", tries >= 3 ? '/' : ' ', tries >= 2 ? '|' : ' ', tries >= 4 ? '\\' : ' ');
    printf(" |  %c %c\n", tries >= 5 ? '/' : ' ', tries >= 6 ? '\\' : ' ');
    printf("=====\n");
}