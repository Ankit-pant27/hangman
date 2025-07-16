#include <stdio.h>
#include <string.h>

int main() {
    char word[] = "apple";         
    int length = strlen(word);    
    char guessed[20];              
    int i, tries = 0;
    char ch;
    int correct = 0;

    for (i = 0; i < length; i++) {
        guessed[i] = '_';
    }

    printf("Welcome to Hangman!\n");
    printf("Guess the word letter by letter:\n");

    while (tries < 10 && correct < length) {
        printf("\nWord: ");
        for (i = 0; i < length; i++) {
            printf("%c ", guessed[i]);
        }

        printf("\nEnter a letter: ");
        scanf(" %c", &ch);

        int found = 0;
        for (i = 0; i < length; i++) {
            if (word[i] == ch && guessed[i] == '_') {
                guessed[i] = ch;
                correct++;
                found = 1;
            }
        }

        if (!found) {
            printf("Wrong guess!\n");
            tries++;
        } else {
            printf("Correct guess!\n");
        }
    }

    if (correct == length) {
        printf("\nCongratulations! You guessed the word: %s\n", word);
    } else {
        printf("\nGame over! The word was: %s\n", word);
    }

    return 0;
}