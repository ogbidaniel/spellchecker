#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 50
char **load_dictionary(const char *filename, int *word_count)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening dictionary");
        exit(EXIT_FAILURE);
    }

    int count = 0;
}

int main()
{
    char word[20];

    printf("Enter a word: ");
    scanf("%s", word);
    printf("Your word is %s\n", word);
    return 0;
}