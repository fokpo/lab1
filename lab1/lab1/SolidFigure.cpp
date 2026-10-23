#include "SolidFigure.h"
#include "Exceptions.h"
#include "Input.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>

namespace {
    const char* const kTypes[] = { "Parallelepiped", "Cube", "Ball", "Sphere", "Cylinder" };
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

SolidFigure::SolidFigure() : Figure("Parallelepiped", 2, 3), c(4) {
    std::cout << "[SolidFigure] Default constructor called.\n";
}

SolidFigure::SolidFigure(const std::string& figureType, double sizeA, double sizeB, double sizeC)
    : Figure(normalizeType(figureType), sizeA, sizeB), c(sizeC) {
    if (sizeC <= 0) throw InvalidValueException("Size C of a solid figure must be greater than zero.");
    checkSizes(getType(), sizeA, sizeB, sizeC);
    std::cout << "[SolidFigure] Parameterized constructor called.\n";
}

SolidFigure::SolidFigure(const SolidFigure& other) : Figure(other), c(other.c) {
    std::cout << "[SolidFigure] Copy constructor called.\n";
}

SolidFigure::~SolidFigure() {
    std::cout << "[SolidFigure] Destructor called.\n";
}

const char* SolidFigure::supportedTypes() { return "Parallelepiped/Cube/Ball/Sphere/Cylinder"; }

std::string SolidFigure::normalizeType(const std::string& value) {
    return matchType(value, kTypes, kTypesCount);
}

double SolidFigure::getC() const { return c; }

void SolidFigure::setC(double value) {
    if (value <= 0) throw InvalidValueException("Size C must be greater than zero.");
    c = value;
}

void SolidFigure::checkSizes(const std::string& type, double a, double b, double c) {
    if (type == "Cube" && !(nearlyEqual(a, b) && nearlyEqual(b, c)))
        throw InvalidValueException("A cube must have equal edges, but got " + num(a) +
            ", " + num(b) + " and " + num(c) + ".");
}

void SolidFigure::readFromKeyboard(std::string& type, double& a, double& b, double& c) {
    // “ип провер€етс€ до запроса размеров: ошибка выдаЄтс€ сразу.
    type = normalizeType(Input::readNonEmpty(
        std::string("Enter solid figure type (") + supportedTypes() + "): "));
    if (type == "Cube") {
        a = Input::readPositive("Enter the edge of the cube: ");
        b = c = a;
    }
    else if (type == "Ball" || type == "Sphere") {
        a = Input::readPositive("Enter the radius: ");
        b = c = a;
    }
    else if (type == "Cylinder") {
        a = Input::readPositive("Enter the radius of the base (size A): ");
        c = Input::readPositive("Enter the height of the cylinder (size C): ");
        b = a;
    }
    else { // Parallelepiped
        a = Input::readPositive("Enter the length (size A): ");
        b = Input::readPositive("Enter the width (size B): ");
        c = Input::readPositive("Enter the height (size C): ");
    }
}

double SolidFigure::calculate() const {
    const std::string t = getType();
    if (t == "Ball" || t == "Sphere") return 4.0 / 3.0 * kPi * getA() * getA() * getA();
    if (t == "Cylinder") return kPi * getA() * getA() * c; // a Ч радиус, c Ч высота
    return getA() * getB() * c; // параллелепипед и куб
}

void SolidFigure::draw() const {
    std::cout << "Solid figure drawing as a flat schematic:\n";
    const std::string t = getType();
    if (t == "Ball" || t == "Sphere") {
        std::cout << "   .----.\n /        \\\n|          |\n \\        /\n   '----'\n";
    }
    else if (t == "Cylinder") {
        
        std::cout << "          ***\n"
            << "        *     *\n"
            << "       *       *\n"
            << "        *     *\n"
            << "          ***\n"
            << "+---------------------+\n"
            << "|                     |\n"
            << "|                     |\n"
            << "+---------------------+\n"
            << "          ***\n"
            << "        *     *\n"
            << "       *       *\n"
            << "        *     *\n"
            << "          ***\n";
    }
    else if (t == "Cube") {
        
        std::cout << "   +--------+\n"
            << "  /        /|\n"
            << " +--------+ |\n"
            << " |        | |\n"
            << " |        | +\n"
            << " |        |/\n"
            << " +--------+\n";
    }
    else { 
        std::cout << "   +--------+\n  /        /|\n +--------+ |\n |        | +\n |        |/\n +--------+\n";
    }
}

void SolidFigure::show() const {
    std::cout << *this << "\nVolume: " << calculate() << "\n";
    draw();
}

void SolidFigure::edit() {
    // —начала читаем и провер€ем всЄ, и только потом мен€ем объект: при ошибке данные не порт€тс€.
    std::string newType;
    double x, y, z;
    readFromKeyboard(newType, x, y, z);
    setType(newType);
    setA(x);
    setB(y);
    setC(z);
}

FigureKind SolidFigure::getKind() const { return SOLID_FIGURE; }

Figure* SolidFigure::clone() const { return new SolidFigure(*this); }

void SolidFigure::save(std::ostream& out) const {
    out << static_cast<int>(SOLID_FIGURE) << ' ' << std::quoted(getType()) << ' '
        << getA() << ' ' << getB() << ' ' << c << '\n';
}

void SolidFigure::print(std::ostream& out) const {
    out << "[Solid figure] Type: " << getType()
        << ", size A: " << getA() << ", size B: " << getB()
        << ", size C: " << c;
}

SolidFigure& SolidFigure::operator=(const SolidFigure& other) {
    if (this != &other) {
        Figure::operator=(other);
        c = other.c;
    }
    std::cout << "[SolidFigure] Assignment operator called.\n";
    return *this;
}
