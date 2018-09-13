// CIS 343 HW2
//
// file_utils.c
// 
// John C. Doneth

#include <stdio.h>

#include "file_utils.h"

//
// Returns the size of a file on success.
// 
// Returns -1 if given `FILE` is NULL
//
// This function assumes that the platform meaningfully supports SEEK_END 
// Source:  https://stackoverflow.com/a/238609
//
int get_file_size(FILE* file) {

    // Handle invalid arguments
    if (file == NULL){
        fprintf(stderr, "Invalid arguments passed to get_file_size()\n");
        return -1;
    }

    int size = 0;

    fseek(file, 0, SEEK_END);

    size = ftell(file); // get file size based on file seek

    rewind(file); // return to file position 0

    return size;
}

//
// Read a file from `filename` into `buffer`
// 
// Returns the number of bytes read on success.
// Returns -1 if any error occurs.
//
int read_file( char* filename, char **buffer ) {

    // Handle invalid arguments
    if (filename == NULL || buffer == NULL){
        fprintf(stderr, "Invalid arguments passed to read_file()\n");
        return -1;
    }

    // Read in binary mode to ignore newlines, etc.
    FILE* file = fopen(filename, "rb");
    
    // Failed to open for reading
    if (file == NULL) {
        fprintf(stderr, "Failed to open %s for reading\n", filename);
        return -1;
    }

    int file_size = get_file_size(file);

    if (file_size == -1){
        fprintf(stderr, "Failed to get size of file %s\n", filename);
        return -1;
    }

    int bytes_read = fread(*buffer, sizeof(char), file_size, file);

    if (ferror(file) != 0){
        fprintf(stderr, "An error occured during reading %s\n", filename);
        fclose(file);
        return -1;
    }

    fclose(file);

    return bytes_read;
}

//
// Write to a file at `filename` from `buffer` of size `size`.
// 
// Returns the number of bytes written on success.
// Returns -1 if any error occurs.
// 
int write_file( char* filename, char *buffer, int size) {

    int bytes_written = 0;

    // Write in binary to ignores newlines, etc.
    FILE* file = fopen(filename, "wb");

    // The file could not be opened for writing.
    if (file == NULL) {
        fprintf(stderr, "%s could not be opened for writing\n", filename);
        fclose(file);
        return -1;
    }

    bytes_written = fwrite(buffer, sizeof(char), size, file);

    // An error occured while writing to the file.
    if (ferror(file) != 0){
        fprintf(stderr, "An error occured while writing to %s\n", filename);
        fclose(file);
        return -1;
    }

    fclose(file);

    return bytes_written;
}
