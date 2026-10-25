#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

enum class TransactionType {
    Income,
    Expense
};

class Transaction {
private:
    int id;
    TransactionType type;
    long long amountPaise;
    std::string category;
    std::string description;
    std::string date;

public:
    Transaction(int id, TransactionType type,
                long long amountPaise,
                const std::string& category,
                const std::string& description,
                const std::string& date);

    int getId() const;
    TransactionType getType() const;
    long long getAmountPaise() const;
    const std::string& getCategory() const;
    const std::string& getDescription() const;
    const std::string& getDate() const;

    std::string typeToString() const;
};

#endif