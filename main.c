// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "functions.h"

int main() {
    struct user usr, usr1;   // Declare user-defined structures to store user information
    FILE *fp;   
    char filename[50], phone[50], pword[50];
    int opt, choice;
    char cont = 'y', reset_choice;
    float amount;
    int otp, entered_otp;

    clear();   // Clear the terminal screen
    print_colored("\n=== Welcome to Banking Management System ===\n", "\033[1;34m");

    // Display main menu options
    printf("\nChoose an option:\n");
    print_colored("1. Register an Account\n", "\033[1;32m");
    print_colored("2. Login to Account\n", "\033[1;33m");
    print_colored("3. Forgot Password\n", "\033[1;35m");
    separator();
    printf("Your choice:\t");
    scanf("%d", &opt);

    // Handle user selection
    if (opt == 1) {
        register_account();  // Register a new user
    }

    else if (opt == 2) {
        login_user();   // Login to existing account
    }

    else if (opt == 3) {
        forgot_password();  // Recover forgotten password
    }

    else {
        print_colored("\nInvalid selection. Please restart.\n", "\033[1;31m");
    }

    print_colored("\nSession ended. Have a nice day!\n", "\033[1;34m");
    return 0;
}
