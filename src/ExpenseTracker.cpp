#include "ExpenseTracker.h"
#include "Utils.h"


#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <stdexcept>

namespace {
const char* DATA_FILE = "data/transactions.csv";

std::string formatMoney(long long paise) {
    std::ostringstream output;
    output << "Rs. " << paise / 100 << '.'
           << std::setw(2) << std::setfill('0')
           << paise % 100;
    return output.str();
}
}

ExpenseTracker::ExpenseTracker() : nextId(1) {
    loadTransactions();
}

std::size_t ExpenseTracker::transactionCount() const {
    return transactions.size();
}

const Transaction* ExpenseTracker::findTransaction(int id) const {
    for (const auto& transaction : transactions) {
        if (transaction.getId() == id) {
            return &transaction;
        }
    }
    return nullptr;
}

int ExpenseTracker::addTransaction(
    TransactionType type,
    long long amountPaise,
    const std::string& category,
    const std::string& description,
    const std::string& date) {

    if (amountPaise <= 0) {
        throw std::invalid_argument("Amount must be positive.");
    }

    if (category.empty() || category.find('|') != std::string::npos ||
        description.empty() || description.find('|') != std::string::npos) {
        throw std::invalid_argument("Invalid category or description.");
    }

    if (!isValidDate(date)) {
        throw std::invalid_argument("Invalid transaction date.");
    }

    if (nextId == std::numeric_limits<int>::max()) {
        throw std::runtime_error("Transaction ID limit reached.");
    }

    int id = nextId;

    transactions.emplace_back(
        id, type, amountPaise, category, description, date);

    try {
        saveTransactions();
    } catch (...) {
        transactions.pop_back();
        throw;
    }

    ++nextId;
    return id;
}

bool ExpenseTracker::removeTransaction(int id) {
    for (auto it = transactions.begin(); it != transactions.end(); ++it) {
        if (it->getId() == id) {
            Transaction removed = *it;
            std::size_t position =
                static_cast<std::size_t>(it - transactions.begin());

            transactions.erase(it);

            try {
                saveTransactions();
            } catch (...) {
                transactions.insert(
                    transactions.begin() +
                        static_cast<std::vector<Transaction>::difference_type>(
                            position),
                    removed);
                throw;
            }

            return true;
        }
    }

    return false;
}

void ExpenseTracker::listTransactions() const {
    if (transactions.empty()) {
        std::cout << "\nNo transactions recorded.\n";
        return;
    }

    std::cout << '\n'
              << std::left
              << std::setw(6) << "ID"
              << std::setw(12) << "Type"
              << std::setw(14) << "Amount"
              << std::setw(18) << "Category"
              << std::setw(14) << "Date"
              << "Description\n";

    std::cout << std::string(85, '-') << '\n';

    for (const auto& t : transactions) {
        std::cout << std::left
                  << std::setw(6) << t.getId()
                  << std::setw(12) << t.typeToString()
                  << std::setw(14) << formatMoney(t.getAmountPaise())
                  << std::setw(18) << t.getCategory()
                  << std::setw(14) << t.getDate()
                  << t.getDescription() << '\n';
    }
}

void ExpenseTracker::showSummary() const {
    long long income = 0;
    long long expenses = 0;

    for (const auto& t : transactions) {
        if (t.getType() == TransactionType::Income) {
            income += t.getAmountPaise();
        } else {
            expenses += t.getAmountPaise();
        }
    }

    std::cout << "\n===== FINANCIAL SUMMARY =====\n"
              << "Total income   : " << formatMoney(income) << '\n'
              << "Total expenses : " << formatMoney(expenses) << '\n'
              << "Net balance    : " << formatMoney(income - expenses)
              << '\n';
}

void ExpenseTracker::showCategorySummary() const {
    std::map<std::string, long long> totals;

    for (const auto& t : transactions) {
        if (t.getType() == TransactionType::Expense) {
            totals[t.getCategory()] += t.getAmountPaise();
        }
    }

    std::cout << "\n===== EXPENSES BY CATEGORY =====\n";

    if (totals.empty()) {
        std::cout << "No expense records available.\n";
        return;
    }

    for (const auto& entry : totals) {
        std::cout << std::left << std::setw(22) << entry.first
                  << formatMoney(entry.second) << '\n';
    }
}

void ExpenseTracker::showMonthlySummary(int year, int month) const {
    if (year < 1900 || month < 1 || month > 12) {
        throw std::invalid_argument("Invalid month or year.");
    }

    long long income = 0;
    long long expenses = 0;

    for (const auto& t : transactions) {
        const std::string& date = t.getDate();

        int transactionYear = std::stoi(date.substr(0, 4));
        int transactionMonth = std::stoi(date.substr(5, 2));

        if (transactionYear == year && transactionMonth == month) {
            if (t.getType() == TransactionType::Income) {
                income += t.getAmountPaise();
            } else {
                expenses += t.getAmountPaise();
            }
        }
    }

    std::cout << "\n===== MONTHLY SUMMARY =====\n"
              << "Month: " << year << '-'
              << std::setw(2) << std::setfill('0') << month
              << std::setfill(' ') << '\n'
              << "Income   : " << formatMoney(income) << '\n'
              << "Expenses : " << formatMoney(expenses) << '\n'
              << "Net      : " << formatMoney(income - expenses) << '\n';
}

void ExpenseTracker::showHighestSpendingCategory() const {
    std::map<std::string, long long> totals;

    for (const auto& t : transactions) {
        if (t.getType() == TransactionType::Expense) {
            totals[t.getCategory()] += t.getAmountPaise();
        }
    }

    if (totals.empty()) {
        std::cout << "\nNo expenses recorded yet.\n";
        return;
    }

    auto highest = totals.begin();

    for (auto it = totals.begin(); it != totals.end(); ++it) {
        if (it->second > highest->second) {
            highest = it;
        }
    }

    std::cout << "\nHighest spending category: "
              << highest->first << " ("
              << formatMoney(highest->second) << ")\n";
}

void ExpenseTracker::saveTransactions() const {
    std::ofstream file(DATA_FILE, std::ios::trunc);

    if (!file) {
        throw std::runtime_error(
            "Cannot save transactions. Check the data folder.");
    }

    for (const auto& t : transactions) {
        file << t.getId() << '|'
             << t.typeToString() << '|'
             << t.getAmountPaise() << '|'
             << t.getCategory() << '|'
             << t.getDescription() << '|'
             << t.getDate() << '\n';
    }

    if (!file) {
        throw std::runtime_error("Failed to write transaction data.");
    }
}

void ExpenseTracker::loadTransactions() {
    std::ifstream file(DATA_FILE);

    if (!file) {
        return;
    }

    std::string line;
    int maxId = 0;

    while (std::getline(file, line)) {
        std::istringstream row(line);

        std::string idText, typeText, amountText;
        std::string category, description, date, extra;

        if (!std::getline(row, idText, '|') ||
            !std::getline(row, typeText, '|') ||
            !std::getline(row, amountText, '|') ||
            !std::getline(row, category, '|') ||
            !std::getline(row, description, '|') ||
            !std::getline(row, date, '|') ||
            std::getline(row, extra, '|')) {
            continue;
        }

        try {
            int id = std::stoi(idText);
            long long amount = std::stoll(amountText);

            TransactionType type;

            if (typeText == "Income") {
                type = TransactionType::Income;
            } else if (typeText == "Expense") {
                type = TransactionType::Expense;
            } else {
                continue;
            }

            if (id <= 0 || amount <= 0 ||
                category.empty() || description.empty() ||
                !isValidDate(date) || findTransaction(id)) {
                continue;
            }

            // Ensure the entire numeric field was valid.
            if (std::to_string(id) != idText ||
                std::to_string(amount) != amountText) {
                continue;
            }

            transactions.emplace_back(
                id, type, amount, category, description, date);

            if (id > maxId) {
                maxId = id;
            }
        } catch (const std::exception&) {
            // Skip malformed records.
        }
    }

    if (maxId >= std::numeric_limits<int>::max() - 1) {
        throw std::runtime_error("Transaction ID limit reached.");
    }

    nextId = maxId + 1;
}