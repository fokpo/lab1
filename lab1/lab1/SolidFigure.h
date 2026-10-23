#ifndef SOLIDFIGURE_H
#define SOLIDFIGURE_H

#include "Figure.h"


class SolidFigure : public Figure {
private:
    double c;

    // ѕроверка согласованности размеров с типом (например, у куба все рЄбра равны).
    static void checkSizes(const std::string& type, double a, double b, double c);

public:
    SolidFigure();
    SolidFigure(const std::string& type, double sizeA, double sizeB, double sizeC);
    SolidFigure(const SolidFigure& other);
    ~SolidFigure() override;

    static const char* supportedTypes();
    static std::string normalizeType(const std::string& value);
    // ¬вод типа и размеров с клавиатуры. “ип провер€етс€ сразу, а запрашиваютс€
    // только те размеры, которые нужны дл€ выбранной фигуры.
    static void readFromKeyboard(std::string& type, double& a, double& b, double& c);

    double getC() const;
    void setC(double value);

    double calculate() const override;
    void draw() const override;
    void show() const override;
    void edit() override;
    FigureKind getKind() const override;
    Figure* clone() const override;
    void save(std::ostream& out) const override;
    void print(std::ostream& out) const override;

    
    SolidFigure& operator=(const SolidFigure& other);
};

#endif
