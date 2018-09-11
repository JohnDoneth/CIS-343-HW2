// CIS 343 HW2
//
// file_utils.c
// 
// John C. Doneth

#include <stdio.h>

#include "file_utils.h"

// Returns the size of a file on success.
// 
// Returns -1 if given `FILE` is NULL
// 
int get_file_size(FILE* file) {

    if (file == NULL){
        return -1;
    }

    int size = 0;

    fseek(file, 0, SEEK_END);

    size = ftell(file);

    fseek(file, 0, SEEK_SET);

    return size;
}

// Read a file from `filename` into `buffer`
// 
// Returns the number of bytes read on success.
// Returns -1 if any error occurs.
//
int read_file( char* filename, char **buffer ) {

    FILE* file = fopen(filename, "r");
    
    // Failed to open for reading
    if (file == NULL) {
        return -1;
    }

    int bytes_read = fread(*buffer, sizeof(char), get_file_size(file), file);

    if (ferror(file) != 0){
        fclose(file);
        return -1;
    }

    fclose(file);

    return bytes_read;
}

// Write to a file at `filename` from `buffer` of size `size`.
// 
// Returns the number of bytes written on success.
// Returns -1 if any error occurs.
// 
int write_file( char* filename, char *buffer, int size) {

    int bytes_written = 0;

    FILE* file = fopen(filename, "w");

    // The file could not be opened for writing.
    if (file == NULL) {
        return -1;
    }

    bytes_written = fwrite(buffer, sizeof(char), size, file);

    // An error occured while writing to the file.
    if (ferror(file) != 0){
        fclose(file);
        return -1;
    }

    fclose(file);

    return bytes_written;
}
