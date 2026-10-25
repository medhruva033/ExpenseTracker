#include "Utils.h"

#include <cctype>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

int readInt(const std::string& prompt) {
    while (true) {
        std::cout << prompt;

        int value;

        if (std::cin >> value) {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        if (std::cin.eof()) {
            throw std::runtime_error("Input stream closed.");
        }

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Enter a valid whole number.\n";
    }
}

long long readMoneyPaise(const std::string& prompt) {
    while (true) {
        std::string input = readLine(prompt);

        if (input.empty() || input[0] == '-' ||
            input[0] == '+') {
            std::cout << "Enter a positive amount, e.g. 250.50.\n";
            continue;
        }

        std::size_t dot = input.find('.');
        if (dot != std::string::npos &&
            input.find('.', dot + 1) != std::string::npos) {
            std::cout << "Invalid amount format.\n";
            continue;
        }

        std::string whole =
            dot == std::string::npos ? input : input.substr(0, dot);
        std::string fraction =
            dot == std::string::npos ? "" : input.substr(dot + 1);

        if (whole.empty() ||
            (dot != std::string::npos &&
             (fraction.empty() || fraction.size() > 2))) {
            std::cout << "Use at most two decimal places.\n";
            continue;
        }

        bool valid = true;

        for (char c : whole) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                valid = false;
                break;
            }
        }

        for (char c : fraction) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                valid = false;
                break;
            }
        }

        if (!valid) {
            std::cout << "Invalid amount. Example: 1250.50\n";
            continue;
        }

        try {
            long long rupees = std::stoll(whole);

            if (rupees > (std::numeric_limits<long long>::max() - 99) / 100) {
                std::cout << "Amount is too large.\n";
                continue;
            }

            long long paise = rupees * 100;

            if (!fraction.empty()) {
                int extra = std::stoi(fraction);
                if (fraction.size() == 1) {
                    extra *= 10;
                }
                paise += extra;
            }

            if (paise <= 0) {
                std::cout << "Amount must be greater than zero.\n";
                continue;
            }

            return paise;
        } catch (const std::exception&) {
            std::cout << "Amount is too large or invalid.\n";
        }
    }
}

std::string readLine(const std::string& prompt) {
    while (true) {
        std::cout << prompt;

        std::string value;

        if (!std::getline(std::cin, value)) {
            throw std::runtime_error("Input stream closed.");
        }

        if (value.find_first_not_of(" \t\r\n") == std::string::npos) {
            std::cout << "Input cannot be empty.\n";
            continue;
        }

        if (value.find('|') != std::string::npos) {
            std::cout << "The | character is not allowed.\n";
            continue;
        }

        return value;
    }
}

bool isValidDate(const std::string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }

    for (std::size_t i = 0; i < date.size(); ++i) {
        if (i != 4 && i != 7 &&
            !std::isdigit(static_cast<unsigned char>(date[i]))) {
            return false;
        }
    }

    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));

    if (year < 1900 || month < 1 || month > 12) {
        return false;
    }

    const int daysInMonth[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    int maxDay = daysInMonth[month - 1];

    bool leapYear = (year % 400 == 0) ||
                    (year % 4 == 0 && year % 100 != 0);

    if (month == 2 && leapYear) {
        maxDay = 29;
    }

    return day >= 1 && day <= maxDay;
}

std::string readDate(const std::string& prompt) {
    while (true) {
        std::string date = readLine(prompt);

        if (isValidDate(date)) {
            return date;
        }

        std::cout << "Invalid date. Use YYYY-MM-DD, e.g. 2026-10-25.\n";
    }
}