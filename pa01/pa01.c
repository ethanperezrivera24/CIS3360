/*============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Hill cipher
|
| Author: Ethan Perez-Rivera
| Language: c
| To Compile: gcc -o pa01 pa01.c
| To Execute: ./pa01 kX.txt pX.txt
|             where kX.txt is the keytext file input
|             and pX.txt is plaintext file input
| Note:
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis
|
| Class: CIS3360 - Security in Computing - Fall 2026
| Instructor: McAlpin
| Due Date: per assignment
+===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_N 9     // Max rows/cols in 2D key array
#define MAX_LEN 10000   // Max characters possible for plaintext

int readKeyFile(const char *filename, int key[MAX_N][MAX_N], int *n);
int readPlainTextFile(const char *filename, char plaintext[MAX_LEN], int *count);
int hillCypher(char ciphertext[MAX_LEN], char plaintext[MAX_LEN], int key[MAX_N][MAX_N],int n, int count);

int main(int argc, char *argv[]) {
    // Check usage
    if(argc != 3) {
        printf("Usage: %s <keyfile> <plaintextfile>\n", argv[0]);
        return 1;
    }

    // Save keyfile and plaintextfile
    char *keyfile = argv[1];
    char *plaintextfile = argv[2];

    // Read keyfile & return non-zero if error
    int n;
    int key[MAX_N][MAX_N];
    if(readKeyFile(keyfile, key, &n) != 0)
        return 1;
    
    // Print key matrix
    printf("\nKey matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%4d", key[i][j]);
        }
        printf("\n");
    }

    // Read plaintextfile & return non-zero if error
    char plaintext[MAX_LEN];
    int plaintextCount;
    if(readPlainTextFile(plaintextfile, plaintext, &plaintextCount))
        return 1;
    
    // Padding to finish n-sized blocks
    int rem = plaintextCount % n;
    if(rem != 0) {
        int pad = n - rem;
        for(int r = 0; r < pad; r++) {
            plaintext[plaintextCount] = 'x';
            plaintextCount++;
    }
}

    // Print plaintext with a new line every 80 characters
    printf("\nPlaintext:\n");
    for(int k = 0; k < plaintextCount; k++) {
        printf("%c", plaintext[k]);
        if((k + 1) % 80 == 0)
            printf("\n");
    }
    printf("\n");

    // Run cipher calculation on plaintext using key & store in new char array
    char ciphertext[MAX_LEN];
    hillCypher(ciphertext, plaintext, key, n, plaintextCount);

    // Print ciphertext with a new line every 80 characters
    printf("\nCiphertext:\n");
    for(int t = 0; t < plaintextCount; t++) {
        printf("%c", ciphertext[t]);
        if((t + 1) % 80 == 0)
            printf("\n");
    }
    printf("\n");

    return 0;
}

// Reads keyfile & populates 2D int key array & n
int readKeyFile(const char *filename, int key[MAX_N][MAX_N], int *n) {
    FILE *fp = fopen(filename, "r");
    if(!fp) {
        printf("Error: could not open key file %s\n", filename);
        return -1;
    }

    fscanf(fp, "%d", n);

    for(int i = 0; i < *n; i++) {
        for(int j = 0; j < *n; j++) {
            fscanf(fp, "%d", &key[i][j]);
        }
    }

    fclose(fp);
    return 0;
}

// Reads plaintextfile & populates char array sized MAX_LEN & keeps track of # of characters
int readPlainTextFile(const char *filename, char plaintext[MAX_LEN], int *count) {
    FILE *fp = fopen(filename, "r");
    if(!fp) {
        printf("Error: could not open plaintext file %s\n", filename);
        return -1;
    }

    *count = 0;
    int c;

    while((c = fgetc(fp)) != EOF) {
        if(!isalpha(c))
            continue;

        c = tolower(c);
        plaintext[*count] = c;
        (*count)++;
    }

    fclose(fp);
    return 0;
}

// Calculates encrypted text
int hillCypher(char ciphertext[MAX_LEN], char plaintext[MAX_LEN], int key[MAX_N][MAX_N],int n, int plaintextCount) {
    for(int i = 0; i < plaintextCount; i += n) {
        for(int row = 0; row < n; row++) {
            int sum = 0;
            for(int col = 0; col < n; col++) {
                sum += key[row][col] * (plaintext[i + col] - 'a');
            }
            sum = sum % 26;
            ciphertext[i + row] = sum + 'a';
        }
    }
    return 0;
}

/*=============================================================================
| I Ethan Perez-Rivera (et563385) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
| I also affirm that I built, developed, and tested this code without using AI
| to build functions, scripts, or other elements of the submitted code.
+=============================================================================*/