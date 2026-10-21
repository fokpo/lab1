#include "FlatFigure.h"
#include <cmath>
#include <stdexcept>

namespace {
    const double PI = 3.141592653589793;
}

FlatFigure::FlatFigure() : Figure("Rectangle", 2.0, 3.0) {
    std::cout << "[FlatFigure] default constructor called.\n";
}

FlatFigure::FlatFigure(const std::string& figureType, double sideA, double sideB)
    : Figure(figureType, sideA, sideB) {
    if (figureType != "Rectangle" && figureType != "Square" &&
        figureType != "Circle" && figureType != "Triangle") {
        throw std::invalid_argument("Unsupported flat figure type.");
    }
    if (figureType == "Square" && sideA != sideB) {
        throw std::invalid_argument("A square must have equal sides.");
    }
    std::cout << "[FlatFigure] parameterized constructor called.\n";
}

FlatFigure::FlatFigure(const FlatFigure& other) : Figure(other) {
    std::cout << "[FlatFigure] copy constructor called.\n";
}

FlatFigure::~FlatFigure() {
    std::cout << "[FlatFigure] destructor called.\n";
}

//площади
double FlatFigure::calculateArea() const {
    const std::string type = getType();
    if (type == "Circle") return PI * getA() * getA();
    if (type == "Triangle") return getA() * getB() / 2.0;
    return getA() * getB();
}

void FlatFigure::draw() const {
    const std::string type = getType();
    std::cout << "Schematic drawing of " << type << ":\n";
    if (type == "Circle") {
        std::cout << "   ***   \n *       *\n*         *\n *       *\n   ***   \n";
    }
    else if (type == "Triangle") {
        std::cout << "    /\\\n   /  \\\n  /____\\\n";
    }
    else {
        std::cout << "+----------+\n|          |\n|          |\n+----------+\n";
    }
}

void FlatFigure::show() const {
    std::cout << *this << "\nArea: " << calculateArea() << "\n";
    draw();
}
