#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <string>

// ¬ид фигуры; используетс€ при сохранении в файл и в Keeper.
enum FigureKind { FLAT_FIGURE = 1, SOLID_FIGURE = 2 };


class Figure {
private:
    
    std::string type;
    double a;
    double b;

protected:
    // ќператор присваивани€ защищЄн, чтобы нельз€ было присвоить плоскую фигуру объЄмной
    // через ссылку на базовый класс (срезка). Ќаследники объ€вл€ют свои операторы.
    Figure& operator=(const Figure& other);

    // »щет значение (без учЄта регистра) в списке допустимых типов,
    // возвращает каноническое написание или бросает InvalidTypeException.
    static std::string matchType(const std::string& value, const char* const* allowed, int allowedCount);

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

    
    virtual double calculate() const = 0;             // площадь или объЄм
    virtual void draw() const = 0;                    // рисунок на экране
    virtual void show() const = 0;                    // полный вывод информации
    virtual void edit() = 0;                          // изменение данных с клавиатуры
    virtual FigureKind getKind() const = 0;
    virtual Figure* clone() const = 0;                // полиморфное копирование
    virtual void save(std::ostream& out) const = 0;
    virtual void print(std::ostream& out) const = 0;  // используетс€ оператором <<
};


std::ostream& operator<<(std::ostream& out, const Figure& figure);

#endif
