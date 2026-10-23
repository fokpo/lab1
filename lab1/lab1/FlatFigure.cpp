#include "FlatFigure.h"
#include "Exceptions.h"
#include "Input.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>

namespace {
    const char* const kTypes[] = { "Rectangle", "Square", "Circle", "Disk", "Triangle" };
    const int kTypesCount = 5;
    const double kPi = 3.141592653589793;

    std::string num(double v) {
        std::ostringstream out;
        out << v;
        return out.str();
    }

    bool nearlyEqual(double x, double y) {
        return std::fabs(x - y) <= 1e-9 * std::max(std::fabs(x), std::fabs(y));
    }
}

FlatFigure::FlatFigure() : Figure("Rectangle", 2, 3) {
    std::cout << "[FlatFigure] Default constructor called.\n";
}

FlatFigure::FlatFigure(const std::string& figureType, double sideA, double sideB)
    : Figure(normalizeType(figureType), sideA, sideB) {
    checkSizes(getType(), sideA, sideB);
    std::cout << "[FlatFigure] Parameterized constructor called.\n";
}

FlatFigure::FlatFigure(const FlatFigure& other) : Figure(other) {
    std::cout << "[FlatFigure] Copy constructor called.\n";
}

FlatFigure::~FlatFigure() {
    std::cout << "[FlatFigure] Destructor called.\n";
}

const char* FlatFigure::supportedTypes() { return "Rectangle/Square/Circle/Disk/Triangle"; }

std::string FlatFigure::normalizeType(const std::string& value) {
    return matchType(value, kTypes, kTypesCount);
}

void FlatFigure::checkSizes(const std::string& type, double a, double b) {
    if (type == "Square" && !nearlyEqual(a, b))
        throw InvalidValueException("A square must have equal sides, but got " +
            num(a) + " and " + num(b) + ".");
}

void FlatFigure::readFromKeyboard(std::string& type, double& a, double& b) {
    // “ип провер€етс€ до запроса размеров: ошибка выдаЄтс€ сразу.
    type = normalizeType(Input::readNonEmpty(
        std::string("Enter flat figure type (") + supportedTypes() + "): "));
    if (type == "Square") {
        a = Input::readPositive("Enter the side of the square: ");
        b = a;
    }
    else if (type == "Circle" || type == "Disk") {
        a = Input::readPositive("Enter the radius: ");
        b = a;
    }
    else if (type == "Triangle") {
        a = Input::readPositive("Enter the height of the triangle (size A): ");
        b = Input::readPositive("Enter the base of the triangle (size B): ");
    }
    else { // Rectangle
        a = Input::readPositive("Enter the width of the rectangle (size A): ");
        b = Input::readPositive("Enter the height of the rectangle (size B): ");
    }
}

double FlatFigure::calculate() const {
    // ƒл€ окружности/круга a Ч радиус; дл€ треугольника a Ч высота, b Ч основание.
    const std::string t = getType();
    if (t == "Circle" || t == "Disk") return kPi * getA() * getA();
    if (t == "Triangle") return getA() * getB() / 2.0;
    return getA() * getB(); // пр€моугольник и квадрат
}

void FlatFigure::draw() const {
    std::cout << "Flat figure drawing (schematic):\n";
    const std::string t = getType();
    if (t == "Circle" || t == "Disk") {
        std::cout << "   ***\n"
            << " *     *\n"
            << "*       *\n"
            << " *     *\n"
            << "   ***\n";
    }
    else if (t == "Triangle") {
        std::cout << "    /\\\n   /  \\\n  /____\\\n";
    }
    else if (t == "Square") {
        
        std::cout << "+--------+\n"
            << "|        |\n"
            << "|        |\n"
            << "|        |\n"
            << "+--------+\n";
    }
    else { 
        std::cout << "+----------+\n|          |\n|          |\n+----------+\n";
    }
}

void FlatFigure::show() const {
    std::cout << *this << "\nArea: " << calculate() << "\n";
    draw();
}

void FlatFigure::edit() {
    // —начала читаем и провер€ем всЄ, и только потом мен€ем объект: при ошибке данные не порт€тс€.
    std::string newType;
    double x, y;
    readFromKeyboard(newType, x, y);
    setType(newType);
    setA(x);
    setB(y);
}

FigureKind FlatFigure::getKind() const { return FLAT_FIGURE; }

Figure* FlatFigure::clone() const { return new FlatFigure(*this); }

void FlatFigure::save(std::ostream& out) const {
    out << static_cast<int>(FLAT_FIGURE) << ' ' << std::quoted(getType()) << ' '
        << getA() << ' ' << getB() << '\n';
}

void FlatFigure::print(std::ostream& out) const {
    out << "[Flat figure] Type: " << getType()
        << ", size A: " << getA() << ", size B: " << getB();
}

FlatFigure& FlatFigure::operator=(const FlatFigure& other) {
    if (this != &other) Figure::operator=(other);
    std::cout << "[FlatFigure] Assignment operator called.\n";
    return *this;
}
