// CIS 343 HW2
//
// file_utils.h
// 
// John C. Doneth

#ifndef FILE_UTILS_H
#define FILE_UTILS_H

// For FILE
#include <stdio.h>

// Returns the size of a file on success.
// 
// Returns -1 if given `FILE` is NULL
//
int get_file_size(FILE* file);

// Read a file from `filename` into `buffer`
// 
// Returns the number of bytes read on success.
// Returns -1 if any error occurs.
//
int read_file(char* filename, char **buffer);

// Write to a file at `filename` from `buffer` of size `size`.
// 
// Returns the number of bytes written on success.
// Returns -1 if any error occurs.
//
int write_file(char* filename, char *buffer, int size);

#endif
