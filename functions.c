// functions.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "utils.h"
#include "functions.h"

// Prompts user to create a password and checks strength
void ask_password(char *output_password) {
    while (1) {
        printf("\nPassword must include:\n");
        printf("- At least 8 characters\n");
        printf("- 1 uppercase letter\n");
        printf("- 1 lowercase letter\n");
        printf("- 1 digit\n");
        printf("- 1 special character\n");
        printf("Set your password: ");
        scanf("%s", output_password);

        if (check_password_strength(output_password))
            break;
        else
            print_colored("Please enter a stronger password.\n", "\033[1;31m");
    }
}

// Evaluates password strength based on character types and length
int check_password_strength(const char *password) {
    int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;
    int length = strlen(password);

    for (int i = 0; i < length; i++) {
        if (isupper(password[i])) has_upper = 1;
        else if (islower(password[i])) has_lower = 1;
        else if (isdigit(password[i])) has_digit = 1;
        else if (ispunct(password[i])) has_special = 1;
    }

    int score = has_upper + has_lower + has_digit + has_special;

    print_colored("Password Strength: ", "\033[1;36m");
    if (length < 8 || score < 2) {
        print_colored("Weak\n", "\033[1;31m");
    } else if (length >= 8 && score == 3) {
        print_colored("Moderate\n", "\033[1;33m");
    } else if (length >= 8 && score == 4) {
        print_colored("Strong\n", "\033[1;32m");
    }

    return (length >= 8 && score == 4);
}

// Generates a 4-digit OTP
int generate_otp() {
    srand(time(0));
    return rand() % 9000 + 1000;
}

// Registers a new user and saves to file  
void register_account() {
    struct user usr;
    FILE *fp;
    char filename[50];

    clear();
    print_colored(">>> Account Registration <<<\n", "\033[1;32m");

    printf("Enter your account number:\t");
    scanf("%s", usr.ac);
    printf("Enter your phone number:\t");
    scanf("%s", usr.phone);
    ask_password(usr.password);     // Prompt user to set a secure password

    usr.balance = 0;
    sprintf(filename, "%s.dat", usr.phone);

    fp = fopen(filename, "wb");
    if (fp == NULL) {
        print_colored("\nError opening file.\n", "\033[1;31m");
        return;
    }

    fwrite(&usr, sizeof(struct user), 1, fp);
    fclose(fp);
    print_colored("\nAccount successfully registered!\n", "\033[1;32m");
}

// Handles user login and banking services
void login_user() {
    struct user usr, usr1;
    FILE *fp;
    char filename[50], phone[50], pword[50];
    int choice, otp, entered_otp;
    char cont = 'y', reset_choice;
    float amount;

    clear();
    print_colored(">>> User Login <<<\n", "\033[1;33m");
    printf("Enter phone number:\t");
    scanf("%s", phone);
    printf("Enter password:\t\t");
    scanf("%s", pword);

    sprintf(filename, "%s.dat", phone);

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        print_colored("\nAccount not found. Please register first.\n", "\033[1;31m");
        return;
    }

    fread(&usr, sizeof(struct user), 1, fp);
    fclose(fp);

    if (!strcmp(pword, usr.password)) {
        do {
            clear();
            print_colored(">>> Welcome ", "\033[1;36m");
            printf("%s!\n", usr.phone);
            separator();
            printf("Select a service:\n");
            printf("1. Balance Inquiry\n");
            printf("2. Deposit Cash\n");
            printf("3. Withdraw Cash\n");
            printf("4. Online Transfer\n");
            printf("5. Change Password\n");
            printf("6. Exit\n");
            separator();
            printf("Enter your choice:\t");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    // Display balance
                    printf("\nYour current balance is Rs. %.2f\n", usr.balance);
                    break;
                case 2:
                    // Deposit amount
                    printf("\nEnter amount to deposit:\t");
                    scanf("%f", &amount);
                    usr.balance += amount;
                    print_colored("\nDeposit successful!\n","\033[1;32m");
                    break;
                case 3:
                    // Withdraw amount
                    printf("\nEnter amount to withdraw:\t");
                    scanf("%f", &amount);
                    if (amount > usr.balance)
                        print_colored("\nInsufficient balance. Withdrawal failed.\n", "\033[1;31m");
                    else
                        usr.balance -= amount;
                        print_colored("\nWithdrawal successful!\n","\033[1;32m");
                    break;
                case 4:
                     // Transfer to another account
                    printf("\nEnter recipient phone number:\t");
                    scanf("%s", phone);
                    printf("Enter amount to transfer:\t");
                    scanf("%f", &amount);
                    if (amount > usr.balance) {
                        print_colored("\nInsufficient balance. Transfer failed.\n", "\033[1;31m");
                        break;
                    }
                    sprintf(filename, "%s.dat", phone);
                    fp = fopen(filename, "rb");
                    if (fp == NULL) {
                        print_colored("\nRecipient not found. Transfer failed\n", "\033[1;31m");
                        break;
                    }
                    sprintf(filename,"%s.dat",phone);
                    fp=fopen(filename,"rb");
                    if (fp==NULL){
                        print_colored("\nRecipient not found. Transfer failed.\n","\033[1;31m");
                        break;
                    }

                    fread(&usr1, sizeof(struct user), 1, fp);
                    fclose(fp);
                    usr1.balance += amount;
                    fp = fopen(filename, "wb");
                    fwrite(&usr1, sizeof(struct user), 1, fp);
                    fclose(fp);

                    sprintf(filename, "%s.dat", usr.phone);
                    usr.balance -= amount;
                    break;
                case 5:
                    // Change password
                    ask_password(usr.password);
                    print_colored("\nPassword changed successfully!\n","\033[1;32m");
                    break;
                case 6:
                    // Exit session
                    print_colored("\nThank you for using our Banking System!\n", "\033[1;34m");
                    return;
                default:
                    print_colored("\nInvalid option! Try again.\n", "\033[1;31m");
            }

            // Save updated user data
            fp = fopen(filename, "wb");
            fwrite(&usr, sizeof(struct user), 1, fp);
            fclose(fp);

            printf("\nDo you want to perform another transaction? (y/n): ");
            scanf(" %c", &cont);
        } while (cont == 'y' || cont == 'Y');
    } else {
        // Incorrect password: offer OTP-based password reset
        print_colored("\nIncorrect password.\n", "\033[1;31m");
        printf("Forgot Password? (y/n): ");
        scanf(" %c", &reset_choice);
        if (reset_choice == 'y' || reset_choice == 'Y') {
            otp = generate_otp();
            printf("Your OTP is: %d\n", otp);
            printf("Enter OTP: ");
            scanf("%d", &entered_otp);
            if (entered_otp == otp) {
                ask_password(usr.password);
                fp = fopen(filename, "wb");
                fwrite(&usr, sizeof(struct user), 1, fp);
                fclose(fp);
                print_colored("\nPassword reset successfully!\n", "\033[1;32m");
            } else {
                print_colored("\nInvalid OTP. Access denied.\n", "\033[1;31m");
            }
        }
    }
}

// Handle forgotten password flow with OTP verification
void forgot_password() {
    struct user usr;
    FILE *fp;
    char filename[50], phone[50];
    int otp, entered_otp;

    clear();
    print_colored(">>> Forgot Password <<<\n", "\033[1;35m");
    printf("Enter your registered phone number:\t");
    scanf("%s", phone);

    sprintf(filename, "%s.dat", phone);

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        print_colored("\nAccount not found.\n", "\033[1;31m");
        return;
    }

    fread(&usr, sizeof(struct user), 1, fp);
    fclose(fp);

    otp = generate_otp();
    printf("Your OTP is: %d (use this to reset password)\n", otp);
    printf("Enter OTP:\t");
    scanf("%d", &entered_otp);

    if (entered_otp == otp) {
        ask_password(usr.password);
        fp = fopen(filename, "wb");
        fwrite(&usr, sizeof(struct user), 1, fp);
        fclose(fp);
        print_colored("\nPassword reset successfully!\n", "\033[1;32m");
    } else {
        print_colored("\nInvalid OTP! Password reset denied.\n", "\033[1;31m");
    }
}
