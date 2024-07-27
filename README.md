# Billing Management System

## Overview

The Billing Management System is a simple console application written in C++ that allows users to manage billing entries. The system provides functionality to:
- Create new billing entries with item details.
- View previous billing entries stored in a CSV file.
- Perform basic calculations, including GST computation and payment handling.

## Features

- **Create New Entry**: Enter details about items including name, quantity, and price. The system calculates the total price for each item, GST, and provides payment details.
- **View Previous Entries**: Read and display previously recorded billing entries from a CSV file.
- **Handle Payments**: Ensure the cash given is sufficient and compute any change required.

## Requirements

- A C++ compiler (e.g., g++, clang++)
- Basic understanding of C++ standard libraries and file handling

## Files

- `main.cpp`: The main source file containing the implementation of the billing system.
- `database.csv`: The file where billing entries are stored. Created automatically when new entries are made.

## Compilation

To compile the `main.cpp` file, use the following command:

```sh
g++ -o billing_system main.cpp
