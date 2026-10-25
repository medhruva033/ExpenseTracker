#include "Transaction.h"

Transaction::Transaction(
    int transactionId,
    TransactionType transactionType,
    long long amount,
    const std::string& transactionCategory,
    const std::string& transactionDescription,
    const std::string& transactionDate)
    : id(transactionId),
      type(transactionType),
      amountPaise(amount),
      category(transactionCategory),
      description(transactionDescription),
      date(transactionDate) {}

int Transaction::getId() const {
    return id;
}

TransactionType Transaction::getType() const {
    return type;
}

long long Transaction::getAmountPaise() const {
    return amountPaise;
}

const std::string& Transaction::getCategory() const {
    return category;
}

const std::string& Transaction::getDescription() const {
    return description;
}

const std::string& Transaction::getDate() const {
    return date;
}

std::string Transaction::typeToString() const {
    return type == TransactionType::Income ? "Income" : "Expense";
}