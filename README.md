# Expense Tracker (C++)

A console-based personal finance manager built with C++17.

## Features

- Record income and expenses
- Categorize transactions
- List and remove transactions
- Calculate total income, expenses, and net balance
- Generate monthly summaries
- Analyze spending by category
- Find the highest-spending category
- Persist transactions between runs
- Validate monetary amounts and dates

## Concepts

- Object-Oriented Programming
- STL vectors and maps
- Encapsulation
- File handling and serialization
- Date validation
- Exception handling
- Integer-based monetary calculations

## Build and Run

### Windows (G++)

From the project root:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -Iinclude src/main.cpp src/Transaction.cpp src/ExpenseTracker.cpp src/Utils.cpp -o expense_tracker.exe
expense_tracker.exe