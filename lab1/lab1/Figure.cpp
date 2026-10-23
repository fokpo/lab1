#include "Figure.h"
#include "Exceptions.h"
#include <cctype>

namespace {
    std::string toLower(const std::string& s) {
        std::string result = s;
        for (std::string::size_type i = 0; i < result.size(); ++i)
            result[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(result[i])));
        return result;
    }
}

Figure::Figure() : type("Undefined"), a(1), b(1) {
    std::cout << "[Figure] Default constructor called.\n";
}

Figure::Figure(const std::string& typeValue, double av, double bv)
    : type(typeValue), a(av), b(bv) {
    if (typeValue.empty()) throw InvalidValueException("Figure type must not be empty.");
    if (av <= 0 || bv <= 0) throw InvalidValueException("Figure sizes must be greater than zero.");
    std::cout << "[Figure] Parameterized constructor called.\n";
}

Figure::Figure(const Figure& other) : type(other.type), a(other.a), b(other.b) {
    std::cout << "[Figure] Copy constructor called.\n";
}

Figure::~Figure() {
    std::cout << "[Figure] Virtual destructor called.\n";
}

std::string Figure::getType() const { return type; }
double Figure::getA() const { return a; }
double Figure::getB() const { return b; }

void Figure::setType(const std::string& value) {
    if (value.empty()) throw InvalidValueException("Figure type must not be empty.");
    type = value;
}
void Figure::setA(double value) {
    if (value <= 0) throw InvalidValueException("Size A must be greater than zero.");
    a = value;
}
void Figure::setB(double value) {
    if (value <= 0) throw InvalidValueException("Size B must be greater than zero.");
    b = value;
}

Figure& Figure::operator=(const Figure& other) {
    if (this != &other) {
        type = other.type;
        a = other.a;
        b = other.b;
    }
    std::cout << "[Figure] Assignment operator called.\n";
    return *this;
}

std::string Figure::matchType(const std::string& value, const char* const* allowed, int allowedCount) {
    std::string lowered = toLower(value);
    for (int i = 0; i < allowedCount; ++i)
        if (lowered == toLower(allowed[i])) return allowed[i];
    throw InvalidTypeException("Unsupported figure type: \"" + value + "\".");
}

std::ostream& operator<<(std::ostream& out, const Figure& figure) {
    figure.print(out);
    return out;
}
