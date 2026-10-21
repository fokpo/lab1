#include "Figure.h"
#include <stdexcept>

//конструкторы+ловля ошибок
Figure::Figure() : type("Undefined"), a(1.0), b(1.0) {
    std::cout << "[Figure] default constructor called.\n";
}

Figure::Figure(const std::string& typeValue, double sideA, double sideB)
    : type(typeValue), a(sideA), b(sideB) {
    if (type.empty()) {
        throw std::invalid_argument("Figure type cannot be empty.");
    }
    if (a <= 0.0 || b <= 0.0) {
        throw std::invalid_argument("Figure dimensions must be positive.");
    }
    std::cout << "[Figure] parameterized constructor called.\n";
}

Figure::Figure(const Figure& other)
    : type(other.type), a(other.a), b(other.b) {
    std::cout << "[Figure] copy constructor called.\n";
}

Figure::~Figure() {
    std::cout << "[Figure] destructor called.\n";
}

std::string Figure::getType() const { return type; }
double Figure::getA() const { return a; }
double Figure::getB() const { return b; }

void Figure::setType(const std::string& value) {
    if (value.empty()) throw std::invalid_argument("Figure type cannot be empty.");
    type = value;
}

void Figure::setA(double value) {
    if (value <= 0.0) throw std::invalid_argument("Dimension A must be positive.");
    a = value;
}

void Figure::setB(double value) {
    if (value <= 0.0) throw std::invalid_argument("Dimension B must be positive.");
    b = value;
}

//перегрузка операторов
std::ostream& operator<<(std::ostream& out, const Figure& figure) {
    out << "Type: " << figure.getType()
        << ", size A: " << figure.getA()
        << ", size B: " << figure.getB();
    return out;
}
