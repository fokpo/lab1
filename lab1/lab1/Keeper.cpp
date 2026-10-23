#include "Keeper.h"
#include "Exceptions.h"
#include "FlatFigure.h"
#include "SolidFigure.h"
#include <fstream>
#include <iomanip>

Keeper::Keeper() : items(nullptr), count(0), capacity(0) {
    std::cout << "[Keeper] Default constructor called.\n";
}

Keeper::Keeper(const Keeper& other) : items(nullptr), count(0), capacity(0) {
    std::cout << "[Keeper] Copy constructor called.\n";
    items = cloneArray(other.items, other.count);
    count = capacity = other.count;
}

Keeper::~Keeper() {
    std::cout << "[Keeper] Destructor called.\n";
    clear();
}

Figure** Keeper::cloneArray(Figure* const* source, int size) {
    if (size == 0) return nullptr;
    Figure** result = new Figure * [size];
    int made = 0;
    try {
        for (; made < size; ++made) result[made] = source[made]->clone();
    }
    catch (...) {
        for (int i = 0; i < made; ++i) delete result[i];
        delete[] result;
        throw;
    }
    return result;
}

void Keeper::clear() {
    for (int i = 0; i < count; ++i) delete items[i];
    delete[] items;
    items = nullptr;
    count = 0;
    capacity = 0;
}

void Keeper::swap(Keeper& other) {
    Figure** tmpItems = items;  items = other.items;  other.items = tmpItems;
    int tmpCount = count;       count = other.count;  other.count = tmpCount;
    int tmpCap = capacity;      capacity = other.capacity;  other.capacity = tmpCap;
}

void Keeper::resize(int newCapacity) {
    Figure** newItems = new Figure * [newCapacity];
    for (int i = 0; i < count; ++i) newItems[i] = items[i];
    delete[] items;
    items = newItems;
    capacity = newCapacity;
}

int Keeper::getCount() const { return count; }

void Keeper::add(Figure* item) {
    if (item == nullptr) throw InvalidValueException("Cannot add an empty object to the keeper.");
    if (count == capacity) {
        try {
            resize(capacity == 0 ? 2 : capacity * 2);
        }
        catch (...) {
            delete item; // объект уже принадлежит Keeper, не допускаем утечки
            throw;
        }
    }
    items[count++] = item;
    std::cout << "Object added to the keeper.\n";
}

void Keeper::remove(int index) {
    if (index < 0 || index >= count) throw IndexOutOfRangeException("There is no object with this number.");
    delete items[index];
    for (int i = index; i < count - 1; ++i) items[i] = items[i + 1];
    --count;
    std::cout << "Object removed.\n";
}

void Keeper::showAll() const {
    if (count == 0) {
        std::cout << "The keeper is empty.\n";
        return;
    }
    for (int i = 0; i < count; ++i) {
        std::cout << "\nObject #" << i + 1 << ":\n";
        items[i]->show(); // Полиморфный вызов метода наследника.
    }
}

void Keeper::edit(int index) {
    (*this)[index].edit();
}

Figure& Keeper::operator[](int index) {
    if (index < 0 || index >= count) throw IndexOutOfRangeException("There is no object with this number.");
    return *items[index];
}

const Figure& Keeper::operator[](int index) const {
    if (index < 0 || index >= count) throw IndexOutOfRangeException("There is no object with this number.");
    return *items[index];
}

void Keeper::saveToFile(const std::string& filename) const {
    std::ofstream out(filename.c_str());
    if (!out) throw FileException("Could not open the file for writing: " + filename);
    out << count << '\n';
    for (int i = 0; i < count; ++i) items[i]->save(out);
    out.flush();
    if (!out) throw FileException("Error while writing data to the file: " + filename);
    std::cout << "Keeper saved to file: " << filename << "\n";
}

void Keeper::loadFromFile(const std::string& filename) {
    std::ifstream in(filename.c_str());
    if (!in) throw FileException("Could not open the file for reading: " + filename);
    int loadedCount;
    if (!(in >> loadedCount) || loadedCount < 0)
        throw FileException("The file contains an invalid number of objects.");

    // Сначала читаем во временный контейнер; текущие данные не теряются при ошибке чтения.
    Keeper temp;
    for (int i = 0; i < loadedCount; ++i) {
        int kind;
        std::string figureType;
        double a, b, c;
        if (!(in >> kind >> std::quoted(figureType) >> a >> b))
            throw FileException("Could not read figure data from the file.");
        if (kind == FLAT_FIGURE) {
            temp.add(new FlatFigure(figureType, a, b));
        }
        else if (kind == SOLID_FIGURE) {
            if (!(in >> c)) throw FileException("Could not read the third size of a solid figure.");
            temp.add(new SolidFigure(figureType, a, b, c));
        }
        else {
            throw FileException("The file contains an unknown object kind.");
        }
    }
    swap(temp); // без повторного копирования; старое содержимое уйдёт вместе с temp
    std::cout << "Keeper restored from file: " << filename << "\n";
}

Keeper& Keeper::operator=(const Keeper& other) {
    if (this == &other) return *this;
    Figure** copy = cloneArray(other.items, other.count); // при ошибке текущие данные не затронуты
    clear();
    items = copy;
    count = capacity = other.count;
    std::cout << "[Keeper] Assignment operator called.\n";
    return *this;
}
