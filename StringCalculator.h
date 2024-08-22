#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Helper function to parse numbers from the input
int parse_number(char* buffer) {
    return atoi(buffer);
}

// Helper function to handle delimiters and custom delimiters
char get_delimiter(const char** input) {
    if (**input == '/' && (*input)[1] == '/') {
        char delimiter = (*input)[2];
        *input += 4; // Skip over "//[delimiter]\n"
        return delimiter;
    }
    return ',';
}

// Main add function
int add(const char* input) {
    if (input == NULL || *input == '\0') {
        return 0;
    }

    char delimiter = get_delimiter(&input);
    int sum = 0;
    char buffer[256];
    int buffer_index = 0;
    int number;

    while (*input) {
        if (*input == delimiter || *input == '\n') {
            buffer[buffer_index] = '\0';
            number = parse_number(buffer);
            if (number < 0) {
                fprintf(stderr, "negatives not allowed\n");
                exit(1);
            } else if (number <= 1000) {
                sum += number;
            }
            buffer_index = 0;
        } else {
            buffer[buffer_index++] = *input;
        }
        input++;
    }
    buffer[buffer_index] = '\0';
    number = parse_number(buffer);
    if (number < 0) {
        fprintf(stderr, "negatives not allowed\n");
        exit(1);
    } else if (number <= 1000) {
        sum += number;
    }

    return sum;
}
