#ifndef EXPENSE_TRACKER_H
#define EXPENSE_TRACKER_H

#include "Transaction.h"

#include <string>
#include <vector>

class ExpenseTracker {
private:
    std::vector<Transaction> transactions;
    int nextId;

    void loadTransactions();
    void saveTransactions() const;

    const Transaction* findTransaction(int id) const;

public:
    ExpenseTracker();

    int addTransaction(TransactionType type,
                       long long amountPaise,
                       const std::string& category,
                       const std::string& description,
                       const std::string& date);

    bool removeTransaction(int id);

    void listTransactions() const;
    void showSummary() const;
    void showCategorySummary() const;
    void showMonthlySummary(int year, int month) const;
    void showHighestSpendingCategory() const;

    std::size_t transactionCount() const;
};

#endif