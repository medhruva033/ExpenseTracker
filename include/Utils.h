#ifndef UTILS_H
#define UTILS_H

#include <string>

int readInt(const std::string& prompt);
long long readMoneyPaise(const std::string& prompt);
std::string readLine(const std::string& prompt);
std::string readDate(const std::string& prompt);
bool isValidDate(const std::string& date);

#endif