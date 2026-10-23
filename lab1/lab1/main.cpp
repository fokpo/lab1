#include <iostream>
#include <string>
#include "Exceptions.h"
#include "FlatFigure.h"
#include "Input.h"
#include "Keeper.h"
#include "SolidFigure.h"

// ¬вод параметров плоской фигуры с клавиатуры; объект создаЄтс€ динамически.
Figure* createFlat() {
    std::string type;
    double a, b;
    FlatFigure::readFromKeyboard(type, a, b);
    return new FlatFigure(type, a, b);
}

// ¬вод параметров объЄмной фигуры с клавиатуры; объект создаЄтс€ динамически.
Figure* createSolid() {
    std::string type;
    double a, b, c;
    SolidFigure::readFromKeyboard(type, a, b, c);
    return new SolidFigure(type, a, b, c);
}

int main() {
    Keeper keeper;
    bool running = true;
    while (running) {
        std::cout << "\n========== LABORATORY WORK #1, VARIANT 13 ==========\n"
            << "1. Add a flat figure\n"
            << "2. Add a solid figure\n"
            << "3. Show all figures\n"
            << "4. Show one figure\n"
            << "5. Edit a figure\n"
            << "6. Delete a figure\n"
            << "7. Save the keeper to a file\n"
            << "8. Restore the keeper from a file\n"
            << "0. Exit\n";
        try {
            int choice = Input::readInt("Choose an action: ");
            switch (choice) {
            case 1:
                keeper.add(createFlat());
                break;
            case 2:
                keeper.add(createSolid());
                break;
            case 3:
                keeper.showAll();
                break;
            case 4: {
                int index = Input::readInt("Enter the figure number to show: ") - 1;
                keeper[index].show();
                break;
            }
            case 5: {
                int index = Input::readInt("Enter the figure number to edit: ") - 1;
                keeper.edit(index);
                std::cout << "Data changed.\n";
                break;
            }
            case 6: {
                int index = Input::readInt("Enter the figure number to delete: ") - 1;
                keeper.remove(index);
                break;
            }
            case 7:
                keeper.saveToFile(Input::readNonEmpty("Enter the file name to save to (e.g. figures.txt): "));
                break;
            case 8:
                keeper.loadFromFile(Input::readNonEmpty("Enter the file name to restore from: "));
                break;
            case 0:
                running = false;
                break;
            default:
                std::cout << "There is no such menu item.\n";
            }
        }
        catch (const InputClosedException& e) {
            // ¬вод закончилс€ (EOF): продолжать цикл бессмысленно.
            std::cout << "Error: " << e.what() << "\n";
            running = false;
        }
        catch (const FigureException& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "Unexpected error: " << e.what() << "\n";
        }
    }
    std::cout << "Program finished.\n";
    return 0;
}
