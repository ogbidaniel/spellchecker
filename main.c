#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 50

char **load_dictionary(char *filename, int *word_count)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening dictionary");
        return NULL;
    }

    int count = 0;
    char buffer[MAX_WORD_LEN];
    while (fgets(buffer, MAX_WORD_LEN, file))
        count++;

    rewind(file);

    char **dictionary = malloc(count * sizeof(char *));
    if (!dictionary) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
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

int is_word_in_dictionary(const char *word, char **dictionary, int word_count) {
    printf("Searching for word: '%s'\n", word);
    for (int i = 0; i < word_count; i++) {
        
        if (strcmp(word, dictionary[i]) == 0)
            return 1;
    }
    return 0;
}

int main()
{
    char dictionary_path[1024]="/home/ogbi/dev/c_cpp/projects/spellchecker/words.txt";
    char word[20];
    int count;
    

    printf("Enter a word: ");
    scanf("%s", word);
  
    char **dictionary = load_dictionary(dictionary_path, &count);
    if (dictionary == NULL) {
        printf("Failed to load dictionary\n");
        return 1;
    }

    if (is_word_in_dictionary(word, dictionary, count) == 1) {
        printf("Spelled Correctly");
    } else {
        printf("Misspelled.");
    }

    // Free allocated memory
    for (int i = 0; i < count; i++) {
        free(dictionary[i]);
    }
    free(dictionary);
    return 0;
}