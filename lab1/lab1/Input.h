#ifndef INPUT_H
#define INPUT_H

#include <string>

// Единая точка ввода с клавиатуры: каждая функция читает строку целиком,
// поэтому в потоке не остаётся "хвостов" и не нужно чистить cin вручную.
namespace Input {
    std::string readLine(const std::string& prompt);      // строка без пробелов по краям
    std::string readNonEmpty(const std::string& prompt);  // непустая строка
    int readInt(const std::string& prompt);               // целое число
    double readPositive(const std::string& prompt);       // вещественное число > 0
}

#endif
