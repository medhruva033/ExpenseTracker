#include "ExpenseTracker.h"
#include "Utils.h"

#include <iostream>
#include <stdexcept>

int main() {
    try {
        ExpenseTracker tracker;

        while (true) {
            std::cout << "\n====================================\n"
                      << "       PERSONAL EXPENSE TRACKER\n"
                      << "====================================\n"
                      << "1. Add income\n"
                      << "2. Add expense\n"
                      << "3. List transactions\n"
                      << "4. Remove transaction\n"
                      << "5. Financial summary\n"
                      << "6. Expenses by category\n"
                      << "7. Monthly summary\n"
                      << "8. Highest spending category\n"
                      << "0. Exit\n";

            int choice = readInt("Enter choice: ");

            try {
                switch (choice) {
                    case 1:
                    case 2: {
                        TransactionType type =
                            choice == 1
                                ? TransactionType::Income
                                : TransactionType::Expense;

                        long long amount =
                            readMoneyPaise("Amount (Rs.): ");

                        std::string category =
                            readLine("Category: ");

                        std::string description =
                            readLine("Description: ");

                        std::string date =
                            readDate("Date (YYYY-MM-DD): ");

                        int id = tracker.addTransaction(
                            type, amount, category, description, date);

                        std::cout << "Transaction saved. ID: "
                                  << id << '\n';
                        break;
                    }

                    case 3:
                        tracker.listTransactions();
                        break;

                    case 4: {
                        int id = readInt("Transaction ID to remove: ");

                        if (tracker.removeTransaction(id)) {
                            std::cout << "Transaction removed.\n";
                        } else {
                            std::cout << "Transaction ID not found.\n";
                        }
                        break;
                    }

                    case 5:
                        tracker.showSummary();
                        break;

                    case 6:
                        tracker.showCategorySummary();
                        break;

                    case 7: {
                        int year = readInt("Year (e.g. 2026): ");
                        int month = readInt("Month (1-12): ");

                        tracker.showMonthlySummary(year, month);
                        break;
                    }

                    case 8:
                        tracker.showHighestSpendingCategory();
                        break;

                    case 0:
                        std::cout << "Expense Tracker closed.\n";
                        return 0;

                    default:
                        std::cout << "Invalid menu choice.\n";
                }
            } catch (const std::exception& error) {
                std::cout << "Operation failed: "
                          << error.what() << '\n';
            }
        }
    } catch (const std::exception& error) {
        std::cerr << "Fatal error: " << error.what() << '\n';
        return 1;
    }
}