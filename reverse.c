// CIS 343 HW2
//
// reverse.c
// 
// John C. Doneth

#include <stdio.h>
#include <stdlib.h>

#include "file_utils.h"

//
// Reverse a buffer in-place without allocating a second buffer
// 
// The function simply keeps a index to the front of the buffer, and a
// index to the end and slowly moves each index to the middle of the 
// buffer, swapping each byte along the way.
//
// Source: https://stackoverflow.com/a/5361899
//
void reverse(char* buffer, int size) {
      
    int right = size-1;
    int left = 0;
    while (left < right) {
        char c = buffer[right];
        buffer[right] = buffer[left];
        buffer[left] = c;
        ++left;
        --right;
    }
    
}

//
// Reverses the binary contents of a file into a file.
//
// Usage:
//      reverse <input-filename> <output-filename>
//      
int main(int argc, char** argv){

    if (argc != 3) {
        printf("Expected 2 arguments, found %d!\n", argc - 1);
        printf("Usage:\n");
        printf("\treverse <input-filename> <output-filename>\n");
    }
    else {

        char* input_filename = argv[1];
        char* output_filename = argv[2];

        // Open the file so we can see how big it is
        FILE* input_file = fopen(input_filename, "r");

        if (input_file == NULL){
            fprintf(stderr, 
                    "Failed to open %s for reading.\n", 
                    input_filename);

            return -1;
        }

        // Run our size detect function
        int input_file_size = get_file_size(input_file);

        fclose(input_file);
        
        // Allocate a buffer to contain the size of the input file
        char* buffer = (char*)malloc(sizeof(char) * input_file_size);
        if (buffer == NULL){
            fprintf(stderr, "Failed to allocate %I64d byte(s).\n", sizeof(char) * input_file_size);
            return -1;
        }

        // Read the file into the allocated buffer
        int bytes_read = read_file(input_filename, &buffer);

        if (bytes_read != -1){

            // Reverse the contents of the buffer in-place
            reverse(buffer, input_file_size);

            // Write the buffer to the output file
            int bytes_written = write_file(
                    output_filename, 
                    buffer, 
                    input_file_size);
           
            // Handle an error if it occured
            if (bytes_written == -1) {
                fprintf(stderr, 
                        "Failed to write to file '%s'.\n", 
                        output_filename);
            }

        } else {
            fprintf(stderr, 
                    "Failed to open file '%s' for reading.\n", 
                    input_filename);
        }

        // Free our memory! Goodbye sweet bytes, you served us well.
        free(buffer);

    }

    // Everything worked!
    return 0;
}
