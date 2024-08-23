#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to check if a string is empty or NULL
int isEmptyString(const char* str) {
    return (str == NULL || str[0] == '\0');
}

// Function to convert a string to an integer and return it if it's less than 1000
int parseNumberIfLessThanThousand(const char* str) {
    int number = atoi(str); // Convert string to integer
    return (number < 1000) ? number : 0;
}

// Function to calculate the sum of numbers in the input string with the given delimiter
int calculateSum(const char* input, const char* delimiter) {
    int sum = 0;
    char* duplicatedInput = strdup(input); // Duplicate the input string
    char* token = strtok(duplicatedInput, delimiter); // Tokenize the input string

    while (token != NULL) {
        sum += parseNumberIfLessThanThousand(token); // Add valid numbers less than 1000 to the sum
        token = strtok(NULL, delimiter);
    }

    free(duplicatedInput); // Free allocated memory
    return sum;
}

// Function to extract a custom delimiter from the input string
void extractCustomDelimiter(const char* input, char* delimiter) {
    int i = 2; // Start after "//"
    while (input[i] != '\n' && input[i] != '\0') {
        delimiter[strlen(delimiter)] = input[i]; // Append character to delimiter
        i++;
    }
    delimiter[strlen(delimiter)] = '\0'; // Null-terminate the delimiter string
}

// Function to check and set the custom delimiter
void setDelimiter(const char* input, char* delimiter) {
    if (input[0] == '/' && input[1] == '/') {
        strcpy(delimiter, ""); // Initialize delimiter string
        extractCustomDelimiter(input, delimiter); // Extract custom delimiter
    } else {
        strcpy(delimiter, ",\n"); // Default delimiters
    }
}

// Main function to add numbers in the input string
int add(const char* input) {
    char delimiter[128]; // Delimiter string

    if (isEmptyString(input)) {
        return 0; // Return 0 if the input string is empty
    }

    setDelimiter(input, delimiter); // Check for custom delimiter
    return calculateSum(input, delimiter); // Calculate and return the sum
}
