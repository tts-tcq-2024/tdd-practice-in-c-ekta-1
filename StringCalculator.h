#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_SIZE 1024
#define MAX_DELIMITER_SIZE 16

void throw_error(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

int is_delimiter(char ch, const char *delimiters) {
    while (*delimiters) {
        if (ch == *delimiters) {
            return 1;
        }
        delimiters++;
    }
    return 0;
}

int sum_numbers(const char *input, const char *delimiters) {
    int sum = 0;
    int num;
    char *endptr;
    const char *ptr = input;
    
    while (*ptr) {
        while (isspace(*ptr)) ptr++;
        
        if (*ptr == '\0') break;
        
        num = strtol(ptr, &endptr, 10);
        if (ptr == endptr) break;

        if (num < 0) {
            throw_error("negatives not allowed");
        }
        if (num <= 1000) {
            sum += num;
        }
        
        ptr = endptr;
    }
    return sum;
}

int add(const char *numbers) {
    if (numbers[0] == '\0') {
        return 0;
    }

    // Default delimiter is ',' and '\n'
    char delimiters[MAX_DELIMITER_SIZE] = ",\n";
    const char *ptr = numbers;
    int result = 0;

    // Check if there's a custom delimiter
    if (strncmp(numbers, "//", 2) == 0) {
        ptr = strchr(numbers, '\n');
        if (!ptr) {
            throw_error("Invalid input format");
        }
        ptr++;
        
        char custom_delimiter[MAX_DELIMITER_SIZE] = {0};
        int delimiter_length = ptr - numbers - 2;
        
        if (delimiter_length > 0) {
            if (delimiter_length < MAX_DELIMITER_SIZE) {
                strncpy(custom_delimiter, numbers + 2, delimiter_length);
                custom_delimiter[delimiter_length] = '\0';
            } else {
                throw_error("Delimiter too long");
            }
            
            // Escape special regex characters
            for (int i = 0; i < delimiter_length; i++) {
                if (strchr(".*+?^${}()|[]\\", custom_delimiter[i])) {
                    custom_delimiter[i] = '\\';
                }
            }
            strcat(delimiters, custom_delimiter);
        }
    }

    // Parse and sum numbers
    result = sum_numbers(ptr, delimiters);
    return result;
}

int main() {
    // Test cases
    printf("%d\n", add(""));           // Expected: 0
    printf("%d\n", add("1"));          // Expected: 1
    printf("%d\n", add("1,2"));        // Expected: 3
    printf("%d\n", add("1\n2,3"));     // Expected: 6
    printf("%d\n", add("//;\n1;2"));   // Expected: 3
    printf("%d\n", add("//[***]\n1***2***3")); // Expected: 6

    // Negative number test (should throw error)
    // Uncomment to test
    // printf("%d\n", add("1,-2,3")); // Expected to throw error: negatives not allowed

    // Number greater than 1000
    printf("%d\n", add("2,1001"));     // Expected: 2

    return 0;
}

