#ifndef KEEPER_H
#define KEEPER_H

#include "Figure.h"

class Keeper {
private:
    Figure** items;
    int count;
    int capacity;

    void resize(int newCapacity);
    void clear();
    void swap(Keeper& other);
    // Создаёт новый массив глубоких копий; при ошибке освобождает всё созданное.
    static Figure** cloneArray(Figure* const* source, int size);

public:
    Keeper();
    Keeper(const Keeper& other);
    ~Keeper();

    int getCount() const;
    // Keeper забирает владение объектом, в том числе если добавление завершилось исключением.
    void add(Figure* item);
    void remove(int index);
    void showAll() const;
    void edit(int index);
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    
    Keeper& operator=(const Keeper& other);
    Figure& operator[](int index);
    const Figure& operator[](int index) const;
};

#endif
