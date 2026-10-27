#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doomcc.h"
#include "lexer.h"

void print_usage(const char *prog) {
    printf("Doom-Script Compiler (doomcc) v0.1\n");
    printf("Rip and tear, compile!\n\n");
    printf("Usage: %s [options] file.ds\n\n", prog);
    printf("Options:\n");
    printf("  -o <file>     Output executable name\n");
    printf("  -c            Generate C code only (don't compile)\n");
    printf("  -v            Verbose output\n");
    printf("  -Wall         Enable all warnings\n");
    printf("  -O0/-O1/-O2   Optimization level\n");
    printf("  --help        Show this help\n");
    printf("\n");
    printf("Examples:\n");
    printf("  %s hell.ds -o hell\n");
    printf("  %s hell.ds -c\n");
}

char *read_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "RIP AND TEAR - Cannot open file: %s\n", filename);
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *buffer = (char *)malloc(size + 1);
    if (!buffer) {
        fprintf(stderr, "RIP AND TEAR - Out of memory\n");
        fclose(file);
        return NULL;
    }
    
    fread(buffer, 1, size, file);
    buffer[size] = '\0';
    fclose(file);
    return buffer;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }
    
    if (strcmp(argv[1], "--help") == 0) {
        print_usage(argv[0]);
        return 0;
    }
    
    CompilerOptions opts = {0};
    opts.optimization_level = 0;
    opts.warnings_all = true;
    
    int i = 1;
    while (i < argc && argv[i][0] == '-') {
        if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            opts.output_file = argv[++i];
        } else if (strcmp(argv[i], "-c") == 0) {
            opts.compile_only_c = true;
        } else if (strcmp(argv[i], "-v") == 0) {
            opts.verbose = true;
        } else if (strcmp(argv[i], "-Wall") == 0) {
            opts.warnings_all = true;
        } else if (strcmp(argv[i], "-O0") == 0) {
            opts.optimization_level = 0;
        } else if (strcmp(argv[i], "-O1") == 0) {
            opts.optimization_level = 1;
        } else if (strcmp(argv[i], "-O2") == 0) {
            opts.optimization_level = 2;
        }
        i++;
    }
    
    if (i >= argc) {
        fprintf(stderr, "RIP AND TEAR - No input file specified\n");
        return 1;
    }
    
    opts.input_file = argv[i];
    
    if (opts.verbose) {
        printf("RIP AND TEAR - Compiling %s\n", opts.input_file);
    }
    
    char *source = read_file(opts.input_file);
    if (!source) {
        return 1;
    }
    
    // For now, just test lexer
    if (opts.verbose) {
        printf("Initializing lexer...\n");
        Lexer lexer;
        lexer_init(&lexer, source);
        Token token;
        do {
            token = lexer_next_token(&lexer);
            printf("Token: %s '%s' at line %d\n", token_type_to_string(token.type), token.lexeme, token.line);
        } while (token.type != TOKEN_EOF && token.type != TOKEN_ERROR);
    }
    
    // Generate output filename
    if (!opts.output_file) {
        opts.output_file = "a.out";
    }
    
    printf("RIP AND TEAR - Compilation complete (minimal implementation)\n");
    printf("Output: %s\n", opts.output_file);
    
    free(source);
    return 0;
}
