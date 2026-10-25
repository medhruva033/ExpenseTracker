# Expense Tracker (C++)

A console-based personal finance manager built with **C++17**. It allows users to record income and expenses, analyze spending patterns, and save transaction data between application runs.

## Features

- Record income and expenses
- Categorize transactions
- List and remove transactions
- Calculate total income, expenses, and net balance
- Generate monthly financial summaries
- Analyze spending by category
- Identify the highest-spending category
- Persist transactions between runs
- Validate monetary amounts and dates

## Concepts Demonstrated

- Object-Oriented Programming (OOP)
- STL containers: `vector` and `map`
- Encapsulation
- File handling and data serialization
- Date validation
- Exception handling
- Integer-based monetary calculations

## Project Structure

```text
ExpenseTracker/
├── include/
│   ├── Transaction.h
│   ├── ExpenseTracker.h
│   └── Utils.h
├── src/
│   ├── Transaction.cpp
│   ├── ExpenseTracker.cpp
│   ├── Utils.cpp
│   └── main.cpp
├── data/
├── .gitignore
├── CMakeLists.txt
├── Makefile
└── README.md
```

## Build and Run

### Windows (G++)

Run these commands from the project root:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -Iinclude src/main.cpp src/Transaction.cpp src/ExpenseTracker.cpp src/Utils.cpp -o expense_tracker.exe
.\expense_tracker.exe
```

### Requirements

- A C++17-compatible compiler, such as GCC
- Windows CMD or a compatible terminal

## Usage

Launch the application and select an option from the menu to add income, add expenses, list or remove transactions, or view financial summaries.

Transaction data is stored locally and loaded when the application starts again.

## Future Improvements

- Automated unit tests
- CSV export and import
- Budget limits and alerts
- Search and filter transactions
- Improved reporting and visualizations

## Author

**Dhruva M. K.**

GitHub: [@medhruva033](https://github.com/medhruva033)
