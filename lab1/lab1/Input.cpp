#include "Input.h"
#include "Exceptions.h"
#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <iostream>

namespace {
    std::string trim(const std::string& s) {
        const char* spaces = " \t\r\n";
        std::string::size_type begin = s.find_first_not_of(spaces);
        if (begin == std::string::npos) return "";
        std::string::size_type end = s.find_last_not_of(spaces);
        return s.substr(begin, end - begin + 1);
    }
}

namespace Input {

    std::string readLine(const std::string& prompt) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line))
            throw InputClosedException("Input stream is closed, cannot read more data.");
        return trim(line);
    }

    std::string readNonEmpty(const std::string& prompt) {
        std::string line = readLine(prompt);
        if (line.empty()) throw InvalidValueException("Empty input is not allowed here.");
        return line;
    }

    int readInt(const std::string& prompt) {
        std::string line = readLine(prompt);
        char* end = nullptr;
        errno = 0;
        long value = std::strtol(line.c_str(), &end, 10);
        if (line.empty() || *end != '\0' || errno == ERANGE || value < -2147483647L || value > 2147483647L)
            throw InputException("An integer was expected, got: \"" + line + "\".");
        return static_cast<int>(value);
    }

    double readPositive(const std::string& prompt) {
        std::string line = readLine(prompt);
        char* end = nullptr;
        errno = 0;
        double value = std::strtod(line.c_str(), &end);
        if (line.empty() || *end != '\0' || errno == ERANGE || !std::isfinite(value))
            throw InputException("A number was expected, got: \"" + line + "\".");
        if (value <= 0) throw InvalidValueException("The value must be greater than zero.");
        return value;
    }

} // namespace Input
