#ifndef DOOMCC_H
#define DOOMCC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TOKEN_LENGTH 256
#define MAX_IDENT_LENGTH 128
#define MAX_STRING_LENGTH 1024

typedef struct {
    char *input_file;
    char *output_file;
    bool compile_only_c;  // -c flag
    bool verbose;
    bool warnings_all;
    int optimization_level;
} CompilerOptions;

#endif
