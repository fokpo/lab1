#ifndef SOLIDFIGURE_H
#define SOLIDFIGURE_H

#include "Figure.h"


class SolidFigure : public Figure {
private:
    double c;

public:
    SolidFigure();
    SolidFigure(const std::string& type, double sideA, double sideB, double sideC);
    SolidFigure(const SolidFigure& other);
    ~SolidFigure() override;

    double getC() const;
    void setC(double value);

    double calculateVolume() const;
    void draw() const override;
    void show() const override;
};


std::ostream& operator<<(std::ostream& out, const SolidFigure& figure);

#endif
