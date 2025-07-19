# Bilakshana Bank System

A C-based console application that simulates a basic banking system. This project provides users with features like account registration, secure login, balance management, online transfer, and password recovery—all with a user-friendly interface using colored text output in the terminal.

---

## Project Files
bilakshana-bank-system/
├── main.c // Main program (menu + navigation)
├── functions.c // Banking functions (register, login, transfer, etc.)
├── utils.c // Utility functions (clear screen, colored text, separators)
├── functions.h // Header for function declarations and user structure
├── utils.h // Header for utility functions
├── *.dat // Binary data files created per user (e.g., 9845xxxxxx.dat)

---

## Features
- Account Registration
- Password Strength Enforcement
- Secure Login System
- Balance Inquiry
- Deposit and Withdraw Money
- Online Money Transfer
- OTP-Based Password Reset
- Terminal Color Output for Better UX

---

## Password Requirements
When registering or resetting a password, the following rules apply:
- Minimum 8 characters.
- At least 1 uppercase letter.
- At least 1 lowercase letter.
- At least 1 digit.
- At least 1 special character (e.g., '@','#','!')

Password strength is assessed and shown as:
- Weak (In red color)
- Moderate (In yellow color)
- Strong (In green color )

---

## Data Storage
Each user has a personal '.dat' file, named using phone number, storing:
- Phone number
- Account number
- Password (stored in plain text - for learning only)
- Account balance

---

## Feedback Messages
The system provides real-time feedback on important actions:
- When deposited, it shows "Deposit successful!" message.
- When withdrawaled, it shows "Withdrawal successful!"/"Insufficient balance. Withdrawal failed." message.
- When Online Transfered, it shows "Transfer successful!"/"Insufficient balance or recipient not found." message.
- When password changed, it shows "Password changed successfully!" message.
- When password reset, it shows "Password reset successfully!"/"Invalid OTP!" message.

---

## Limitations
Limitations of my project are given below:
- Passwords are stored in plain text which is not secure.
- No database system; relies on local file storage.
- No input format validation.
- No transaction logs or history tracking.

---

## Future Enhancements
- Use password hashing.
- Add transaction history logs.
- Create admin dashboard to manage all users.
- Include format validation for user inputs.
- Encrypt ".dat" file contents.

