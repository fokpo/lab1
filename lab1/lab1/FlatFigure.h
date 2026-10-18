#ifndef FLATFIGURE_H
#define FLATFIGURE_H

#include "Figure.h"

class FlatFigure : public Figure {
public:
    FlatFigure();
    FlatFigure(const std::string& type, double sideA, double sideB);
    FlatFigure(const FlatFigure& other);
    ~FlatFigure() override;

    double calculateArea() const override;
    void draw() const override;
    void show() const override;
};

#endif
