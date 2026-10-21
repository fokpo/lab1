#include "SolidFigure.h"
#include <cmath>
#include <stdexcept>

namespace {
    const double PI = 3.141592653589793;
}

SolidFigure::SolidFigure() : Figure("Parallelepiped", 2.0, 3.0), c(4.0) {
    std::cout << "[SolidFigure] default constructor called.\n";
}

SolidFigure::SolidFigure(const std::string& figureType, double sideA, double sideB, double sideC)
    : Figure(figureType, sideA, sideB), c(sideC) {
    if (sideC <= 0.0) {
        throw std::invalid_argument("Dimension C must be positive.");
    }
    if (figureType != "Parallelepiped" && figureType != "Cube" &&
        figureType != "Ball" && figureType != "Cylinder") {
        throw std::invalid_argument("Unsupported solid figure type.");
    }
    if (figureType == "Cube" && (sideA != sideB || sideB != sideC)) {
        throw std::invalid_argument("A cube must have equal edges.");
    }
    std::cout << "[SolidFigure] parameterized constructor called.\n";
}

SolidFigure::SolidFigure(const SolidFigure& other) : Figure(other), c(other.c) {
    std::cout << "[SolidFigure] copy constructor called.\n";
}

SolidFigure::~SolidFigure() {
    std::cout << "[SolidFigure] destructor called.\n";
}

double SolidFigure::getC() const { return c; }

void SolidFigure::setC(double value) {
    if (value <= 0.0) throw std::invalid_argument("Dimension C must be positive.");
    c = value;
}

//объемы (шар: a - радиус; цилиндр: a - радиус, c - высота)
double SolidFigure::calculateVolume() const {
    const std::string type = getType();
    if (type == "Ball") return 4.0 / 3.0 * PI * getA() * getA() * getA();
    if (type == "Cylinder") return PI * getA() * getA() * c;
    return getA() * getB() * c;
}

void SolidFigure::draw() const {
    const std::string type = getType();
    std::cout << "Schematic drawing of " << type << " (flat view):\n";
    if (type == "Ball") {
        std::cout << "   .----.\n /        \\\n|          |\n \\        /\n   '----'\n";
    }
    else if (type == "Cylinder") {
        std::cout << "   ______\n /      \\\n|        |\n|        |\n \\______/\n";
    }
    else {
        std::cout << "   +--------+\n  /        /|\n +--------+ |\n |        | +\n |        |/\n +--------+\n";
    }
}

void SolidFigure::show() const {
    std::cout << *this << "\nVolume: " << calculateVolume() << "\n";
    draw();
}

std::ostream& operator<<(std::ostream& out, const SolidFigure& figure) {
    out << static_cast<const Figure&>(figure) << ", size C: " << figure.getC();
    return out;
}
