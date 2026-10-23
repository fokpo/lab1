#ifndef FLATFIGURE_H
#define FLATFIGURE_H

#include "Figure.h"


class FlatFigure : public Figure {
private:
    // Проверка согласованности размеров с типом (например, у квадрата стороны равны).
    static void checkSizes(const std::string& type, double a, double b);

public:
    FlatFigure();
    FlatFigure(const std::string& type, double sideA, double sideB);
    FlatFigure(const FlatFigure& other);
    ~FlatFigure() override;

    // Список допустимых типов для подсказок пользователю и проверка/нормализация типа.
    static const char* supportedTypes();
    static std::string normalizeType(const std::string& value);
    // Ввод типа и размеров с клавиатуры. Тип проверяется сразу, а запрашиваются
    // только те размеры, которые нужны для выбранной фигуры.
    static void readFromKeyboard(std::string& type, double& a, double& b);

    double calculate() const override;
    void draw() const override;
    void show() const override;
    void edit() override;
    FigureKind getKind() const override;
    Figure* clone() const override;
    void save(std::ostream& out) const override;
    void print(std::ostream& out) const override;

    
    FlatFigure& operator=(const FlatFigure& other);
};

#endif
