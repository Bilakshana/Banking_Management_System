// utils.c
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// Clears the terminal screen (cross-platform)
void clear() {
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear");  // For Unix/Linux/Mac
#endif
}

// Prints a separator line for better UI formatting
void separator() {
    printf("\n--------------------------------------------------\n");
}

void print_colored(const char *text, const char *color_code) {
    printf("%s%s\033[0m", color_code, text);
}
