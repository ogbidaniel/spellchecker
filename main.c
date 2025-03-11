#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 50

char **load_dictionary(char *filename, int *word_count)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening dictionary");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    char buffer[MAX_WORD_LEN];
    while (fgets(buffer, MAX_WORD_LEN, file))
        count++;

    rewind(file);

    char **dictionary = malloc(count * sizeof(char *));
    if (!dictionary) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (fgets(buffer, MAX_WORD_LEN, file)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        dictionary[i] = malloc(strlen(buffer) + 1);
        strcpy(dictionary[i], buffer);
        i++;
    }
    fclose(file);

    *word_count = count;
    return dictionary;
}

int main()
{
    char word[20];
    int count;

    // printf("Enter a word: ");
    // scanf("%s", word);
    // printf("Your word is %s\n", word);
    load_dictionary("words.txt", &count);
    printf("Word count: %d", count);
    return 0;
}