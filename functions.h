// functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Structure to store user account information
struct user {
    char phone[50];  // Phone number (used as unique ID)
    char ac[50];     // Account number
    char password[50];   // User password
    float balance;   // Account balance
};

// Checks if a given password is strong 
int check_password_strength(const char *password);

// Prompts user to create a strong password
void ask_password(char *output_password);

// Generates a 4-digit OTP
int generate_otp();

// Handles account registration
void register_account();

// Handles user login and transaction operations
void login_user();

// Handles password recovery via OTP
void forgot_password();

#endif
