// CIS 343 HW2
//
// reverse.c
// 
// John C. Doneth

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for strlen

#include "file_utils.h"

// Reverse a string without allocating a second buffer
// 
// Source: https://stackoverflow.com/a/5361899
//
void reverse(char* str) {
      
    int right = strlen(str) - 1;
    int left = 0;
    while (left < right) {
        char c = str[right];
        str[right] = str[left];
        str[left] = c;
        ++left;
        --right;
    }
    
}

// Usage:
//      reverse INPUT_FILENAME OUTPUT_FILENAME
//
int main(int argc, char** argv){

    if (argc != 3) {
        printf("Expected 2 arguments, found %d!\n", argc - 1);
        printf("Usage:\n");
        printf("\treverse <input-filename> <output-filename>\n");
    }
    else {
        /*printf("Args:\n");

        for (int i = 0; i < argc; i++) {
            printf("Arg %d : '%s'\n", i, argv[i]);
        }*/

        char* input_filename = argv[1];
        char* output_filename = argv[2];

        FILE* input_file = fopen(input_filename, "r");
       
        int input_file_size = get_file_size(input_file);

        fclose(input_file);

        char* buffer = (char*)malloc(sizeof(char) * input_file_size);

        int bytes_read = read_file(input_filename, &buffer);

        if (bytes_read != -1){

            //printf("Bytes read %d from input file.\n", bytes_read);
            printf("Input file contents:\n%s\n", buffer);

            reverse(buffer);

            printf("Reversed:\n%s\n", buffer);

            int bytes_written = write_file(output_filename, buffer, input_file_size);
            if (bytes_written == -1) {
                printf("Failed to write to file '%s'.\n", output_filename);
            }

        } else {
            printf("Failed to open file '%s' for reading\n", input_filename);
        }

    }

}
