#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h>

void sortStrings(char **arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arr[i], arr[j]) > 0) {
                char *temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int isDuplicate(char **arr, int n, const char *word) {
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i], word) == 0) {
            return 1; 
        }
    }
    return 0; 
}

int main() {
    FILE *fpin = fopen("test.txt", "r");
    if (fpin == NULL) return 1;

    FILE *fpout = fopen("result.txt", "w");
    if (fpout == NULL) return 1;

    char **words = NULL;
    char word[100]; 
    int count = 0;
    int wordStarted = 0;
    int symbol;

    while ((symbol = fgetc(fpin)) != EOF) {
        if (isalpha(symbol) || isdigit(symbol)) {
            word[wordStarted] = symbol;
            wordStarted++;
        } else if (wordStarted > 0) {
            word[wordStarted] = '\0';
            wordStarted = 0;

            if (!isDuplicate(words, count, word)) {
                words = (char **)realloc(words, (count + 1) * sizeof(char *));
                words[count] = (char *)malloc(strlen(word) + 1);
                strcpy(words[count], word);
                count++;
            }
        }
    }

    if (wordStarted > 0) {
        word[wordStarted] = '\0';
        wordStarted = 0;

        if (!isDuplicate(words, count, word)) {
            words = (char **)realloc(words, (count + 1) * sizeof(char *));
            words[count] = (char *)malloc(strlen(word) + 1);
            strcpy(words[count], word);
            count++;
        }
    }

    fclose(fpin);
    sortStrings(words, count);

    for (int i = 0; i < count; i++)
        fprintf(fpout, "%s\n", words[i]);

    fclose(fpout);

    for (int i = 0; i < count; i++)
        free(words[i]);

    free(words);
    return 0;
}
