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
        buffer[strcspn(buffer, "\r")] = '\0';
        dictionary[i] = malloc(strlen(buffer) + 1);
        strcpy(dictionary[i], buffer);
        i++;
    }
    fclose(file);

    *word_count = count;
    return dictionary;
}

int is_word_in_dictionary(const char *word, char **dictionary, int word_count) {
    // simple sequential search string matching algorithm
    printf("Searching for word: '%s'\n", word);
    for (int i = 0; i < word_count; i++) {
        
        if (strcmp(word, dictionary[i]) == 0)
            return 1;
    }
    return 0;
}

int min(int a, int b, int c) {
    int m = a < b ? a : b;
    return m < c ? m : c;
}

int levenshtein_distance(const char *s, const char *t) {
    int ls = strlen(s), lt = strlen(t);
    int **d = malloc((ls + 1) * sizeof(int *));
    for (int i = 0; i <= ls; i++)
        d[i] = malloc((lt + 1) * sizeof(int));
    
    for (int i = 0; i <= ls; i++)
        d[i][0] = i;
    for (int j = 0; j <= lt; j++)
        d[0][j] = j;
    
    for (int i = 1; i <= ls; i++) {
        for (int j = 1; j <= lt; j++) {
            int cost = (s[i - 1] == t[j - 1]) ? 0 : 1;
            d[i][j] = min(d[i - 1][j] + 1,     // deletion
                          d[i][j - 1] + 1,     // insertion
                          d[i - 1][j - 1] + cost); // substitution
        }
    }
    
    int distance = d[ls][lt];
    
    // Free the allocated memory.
    for (int i = 0; i <= ls; i++)
        free(d[i]);
    free(d);
    
    return distance;
}

int main()
{
    // path to dictionary
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