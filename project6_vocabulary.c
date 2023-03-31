#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 50
/*
Michael Guy
U59744104
Project 6
*/

/*
The program below will receive two command-line arguments, the name of the input text file and the name of the file where the vocabulary must be saved.
The program then makes a aplhabetically sorted vocabulary list of all words used in the input file.
*/
// Compare function for sort function
int compare(const void* a, const void* b) {
    const char** w1 = (const char**)a;
    const char** w2 = (const char**)b;
    return strcmp(*w1, *w2);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s input_file output_file\n", argv[0]);
        return 1;
    }

    // Open the input file
    FILE* fin = fopen(argv[1], "r");
    if (!fin) {
        printf("Error: cannot open input file '%s'\n", argv[1]);
        return 1;
    }

    // Open the output file
    FILE* fout = fopen(argv[2], "w");
    if (!fout) {
        printf("Error: cannot open output file '%s'\n", argv[2]);
        fclose(fin);
        return 1;
    }

    // Initialize vocab
    char vocab[MAX_WORDS][MAX_WORD_LEN] = {0};
    int word_counts[MAX_WORDS] = {0};
    int num_words = 0;

    // Read the input file
    char word[MAX_WORD_LEN] = {0};
    int c;
    
    while ((c = fgetc(fin)) != EOF) {
        if (isalpha(c)) {
            // Append c to word
            strncat(word, &c, 1);
        } else if (strlen(word) > 0) {
            // Add word to vocabulary
            int i;
            // Convert to uppercase
            for (i = 0; i < strlen(word); i++) {
                word[i] = toupper(word[i]);
            }
         

            // Check if word is already in vocabulary
            int found = 0;
            for (i = 0; i < num_words; i++) {
                if (strcmp(word, vocab[i]) == 0) {
                    found = 1;
                    word_counts[i]++;
                    break;
                }
            }

            // Add new word to vocabulary
            if (!found) {
                strcpy(vocab[num_words], word);
                word_counts[num_words] = 1;
                num_words++;
            }

            // Reset word
            strcpy(word, "");
        }
    }

    // Sort vocabulary by word
    char* sorted_vocab[MAX_WORDS] = {0};
    for (int i = 0; i < num_words; i++) {
        sorted_vocab[i] = vocab[i];
    }
    qsort(sorted_vocab, num_words, sizeof(char*), compare);

    // Save vocabulary to output file
    for (int i = 0; i < num_words; i++) {
        fprintf(fout, "%d %s\n", i+1, sorted_vocab[i]);
    }

    // Close files
    fclose(fin);
    fclose(fout);

    return 0;
}