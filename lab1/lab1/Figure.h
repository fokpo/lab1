#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <string>

class Figure {
private:
    std::string type;
    double a;
    double b;

public:
    Figure();
    Figure(const std::string& type, double a, double b);
    Figure(const Figure& other);
    virtual ~Figure();

    std::string getType() const;
    double getA() const;
    double getB() const;

    void setType(const std::string& value);
    void setA(double value);
    void setB(double value);

    virtual void draw() const = 0;
    virtual void show() const = 0;
};

std::ostream& operator<<(std::ostream& out, const Figure& figure);

#endif
