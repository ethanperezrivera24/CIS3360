/* Assignment: pa02 - Calculate the checksum of an input file given:
|                    -> the name of the input file,
|                    -> the checksum size of either 8, 16, or 32 bits
| Author: Ethan Perez-Rivera
| Language: c
| To Compile: gcc -o pa02 pa02.c
| To Execute: c -> ./pa02 inputFilename.txt checksumSize
|             where inputFilename.txt is the input file
|             and checksumSize is either 8, 16, or 32
| Note:
|     All input files are simple 8 bit ASCII input
|     All execute commands above have been tested on Eustis
| Class: CIS3360 - Security in Computing - Fall 2026
| Instructor: McAlpin
| Due Date: per assignment
+===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#define INIT_CAPACITY 64

int main(int argc, char *argv[]) {
    // check command line input
    if(argc != 3) {
        fprintf(stderr, "Usage: ./pa02 <input file> <checksum size>\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    // check input file can be opened
    if(!fp) {
        fprintf(stderr, "Could not open %s\n", argv[1]);
        return 1;
    }

    int checksumSize = atoi(argv[2]);
    // check that checksumSize is valid
    if(checksumSize != 8 && checksumSize != 16 && checksumSize != 32) {
        fclose(fp);
        fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
        return 1;
    }

    // create array to read file into
    unsigned char *buf = malloc(sizeof(char) * INIT_CAPACITY);
    if(!buf) {
        fclose(fp);
        return 1;
    }
    int count = 0;
    int capacity = INIT_CAPACITY;
    int c;

    // loop through file & increase size of array if necessary
    while((c = fgetc(fp)) != EOF) {
        if (count == capacity) {
            unsigned char *tmp = realloc(buf, sizeof(char) * (capacity * 2));
            if(!tmp) {
                free(buf);
                fclose(fp);
                return 1;
            }
            buf = tmp;
            capacity *= 2;
        }
        buf[count] = (unsigned char)c;
        count++;
    }

    // bytes per word: 1 for 8-bit, 2 for 16-bit, 4 for 32-bit
    int wordBytes = checksumSize / 8;

    // pad with 'X' until count is a multiple of the word size
    // (for 8-bit, wordBytes is 1, so this loop never runs)
    while(count % wordBytes != 0) {
        if (count == capacity) {
            unsigned char *tmp = realloc(buf, sizeof(char) * (capacity * 2));
            if(!tmp) {
                free(buf);
                fclose(fp);
                return 1;
            }
            buf = tmp;
            capacity *= 2;
        }

        buf[count] = 'X';
        count++;
    }

    // blank line before the echoed text
    printf("\n");

    // loop to echo input (now includes any padding)
    for(int i = 0; i < count; i++) {
        printf("%c", buf[i]);

        // make sure its end of row, there's more characters to print, and the next character is not
        // a new line, to avoid cases where there is an unnecessary extra \n
        if((i + 1) % 80 == 0 && i + 1 < count && buf[i + 1] != '\n')
            printf("\n");
    }

    // newline after the echo, before the checksum line
    printf("\n");

    // compute checksum
    unsigned long checksum = 0;

    if(checksumSize == 8) {
        for(int j = 0; j < count; j++)
            checksum += buf[j];

    } else if(checksumSize == 16) {
        for(int j = 0; j < count / 2; j++) {
            unsigned long tmp = ((unsigned long)buf[2*j] << 8) + buf[2*j+1];
            checksum += tmp;
        }

    } else if(checksumSize == 32) {
        for(int j = 0; j < count / 4; j++) {
            unsigned long tmp = ((unsigned long)buf[4*j] << 24) + ((unsigned long)buf[4*j+1] << 16) + ((unsigned long)buf[4*j+2] << 8) + buf[4*j+3];
            checksum += tmp;
        }
    }

    // bitmask based on checksumSize
    switch(checksumSize) {
        case 8:
            checksum = checksum & 0xFF;
            break;

        case 16:
            checksum = checksum & 0xFFFF;
            break;

        case 32:
            checksum = checksum & 0xFFFFFFFF;
            break;
    }

    // output line
    printf("%2d bit checksum is %8lx for all %4d chars\n", checksumSize, checksum, count);

    fclose(fp);
    free(buf);
    return 0;
}


/* I Ethan Perez-Rivera (et563385) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
| I also affirm that I built, developed, and tested this code without using AI
| to build functions, scripts, or other elements of the submitted code.
+=============================================================================*/