# Address Book

This is a simple C-based address book application that allows users to store and manage contact details.
I created this project to practice modular programming in C, dynamic memory allocation, and file handling.

The application supports adding, editing, deleting, and viewing contacts, with data saved to a file for future use.


# Features
- Add new contacts with name, phone number, and email
- Edit existing contact details
- Delete contacts
- View all saved contacts
- Save and load contacts from a text file (`contact.txt`)


# Project Structure
Addressbook/
├── main.c # Entry point of the program
├── contact.c # Implementation of contact-related functions
├── contact.h # Header file with function prototypes
├── contact.txt # File used to store contact data


# Compilation and Execution
To compile and run the program using GCC:

```bash
gcc main.c contact.c -o addressbook
./addressbook
