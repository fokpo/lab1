#include <exception>
#include <iostream>
#include "FlatFigure.h"

//тест работы создания плоских фигур и расчета площадей
int main() {
    try {
        FlatFigure rectangle("Rectangle", 4.0, 5.0);
        FlatFigure circle("Circle", 3.0, 3.0);
        FlatFigure triangle("Triangle", 4.0, 6.0);

        std::cout << "=== Rectangle ===\n";
        rectangle.show();
        std::cout << "\n=== Circle ===\n";
        circle.show();
        std::cout << "\n=== Triangle ===\n";
        triangle.show();
    } catch (const std::exception& error) {
        std::cout << "Error: " << error.what() << "\n";
        return 1;
    }

    return 0;
}
