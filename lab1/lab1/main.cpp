#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include "FlatFigure.h"
#include "SolidFigure.h"


int readInt(const std::string& text) {
    std::cout << text;
    int value;
    if (!(std::cin >> value)) {
        if (std::cin.eof()) throw std::runtime_error("Input stream is closed.");
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        throw std::invalid_argument("An integer was expected.");
    }
    return value;
}


double readNumber(const std::string& text) {
    std::cout << text;
    double value;
    if (!(std::cin >> value)) {
        if (std::cin.eof()) throw std::runtime_error("Input stream is closed.");
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        throw std::invalid_argument("A number was expected.");
    }
    return value;
}


std::string chooseFlatType() {
    std::cout << "1 - Rectangle, 2 - Square, 3 - Circle, 4 - Triangle\n";
    int number = readInt("Choose the figure type: ");
    if (number == 1) return "Rectangle";
    if (number == 2) return "Square";
    if (number == 3) return "Circle";
    if (number == 4) return "Triangle";
    throw std::invalid_argument("There is no flat figure with this number.");
}

std::string chooseSolidType() {
    std::cout << "1 - Parallelepiped, 2 - Cube, 3 - Ball, 4 - Cylinder\n";
    int number = readInt("Choose the figure type: ");
    if (number == 1) return "Parallelepiped";
    if (number == 2) return "Cube";
    if (number == 3) return "Ball";
    if (number == 4) return "Cylinder";
    throw std::invalid_argument("There is no solid figure with this number.");
}


FlatFigure* createFlat() {
    std::string type = chooseFlatType();
    double a, b;
    if (type == "Square") {
        a = readNumber("Side: ");
        b = a;
    }
    else if (type == "Circle") {
        a = readNumber("Radius: ");
        b = a;
    }
    else if (type == "Triangle") {
        a = readNumber("Height: ");
        b = readNumber("Base: ");
    }
    else {
        a = readNumber("Width: ");
        b = readNumber("Height: ");
    }
    return new FlatFigure(type, a, b);
}

SolidFigure* createSolid() {
    std::string type = chooseSolidType();
    double a, b, c;
    if (type == "Cube") {
        a = readNumber("Edge: ");
        b = a;
        c = a;
    }
    else if (type == "Ball") {
        a = readNumber("Radius: ");
        b = a;
        c = a;
    }
    else if (type == "Cylinder") {
        a = readNumber("Base radius: ");
        c = readNumber("Height: ");
        b = a;
    }
    else {
        a = readNumber("Length: ");
        b = readNumber("Width: ");
        c = readNumber("Height: ");
    }
    return new SolidFigure(type, a, b, c);
}

//простое меню: пока по одной фигуре каждого вида, без контейнера Keeper
int main() {
    FlatFigure* flat = nullptr;
    SolidFigure* solid = nullptr;
    bool running = true;

    while (running) {
        std::cout << "\n===== MENU =====\n"
            << "1. Create a flat figure\n"
            << "2. Create a solid figure\n"
            << "3. Show the flat figure\n"
            << "4. Show the solid figure\n"
            << "5. Delete both figures\n"
            << "0. Exit\n";
        try {
            int choice = readInt("Your choice: ");
            if (choice == 1) {
                FlatFigure* created = createFlat();
                delete flat; //старую фигуру удаляем только когда новая успешно создана
                flat = created;
            }
            else if (choice == 2) {
                SolidFigure* created = createSolid();
                delete solid;
                solid = created;
            }
            else if (choice == 3) {
                if (flat) flat->show();
                else std::cout << "The flat figure has not been created yet.\n";
            }
            else if (choice == 4) {
                if (solid) solid->show();
                else std::cout << "The solid figure has not been created yet.\n";
            }
            else if (choice == 5) {
                delete flat;
                delete solid;
                flat = nullptr;
                solid = nullptr;
            }
            else if (choice == 0) {
                running = false;
            }
            else {
                std::cout << "There is no such menu item.\n";
            }
        }
        catch (const std::invalid_argument& error) {

            std::cout << "Error: " << error.what() << "\n";
        }
        catch (const std::exception& error) {

            std::cout << "Error: " << error.what() << "\n";
            running = false;
        }
    }

    delete flat;
    delete solid;
    return 0;
}
