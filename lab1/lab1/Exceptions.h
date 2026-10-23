#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

// ТРЕБОВАНИЕ: собственная иерархия исключений, каждое исключение несёт поясняющий текст.
class FigureException : public std::runtime_error {
public:
    explicit FigureException(const std::string& message);
};

// Недопустимое значение (нулевой/отрицательный размер, пустая строка, пустой указатель).
class InvalidValueException : public FigureException {
public:
    explicit InvalidValueException(const std::string& message);
};

// Неподдерживаемый тип фигуры.
class InvalidTypeException : public FigureException {
public:
    explicit InvalidTypeException(const std::string& message);
};

// Номер объекта вне диапазона хранилища.
class IndexOutOfRangeException : public FigureException {
public:
    explicit IndexOutOfRangeException(const std::string& message);
};

// Ошибка работы с файлом.
class FileException : public FigureException {
public:
    explicit FileException(const std::string& message);
};

// Ошибка разбора введённых пользователем данных.
class InputException : public FigureException {
public:
    explicit InputException(const std::string& message);
};

// Поток ввода закрыт (EOF), дальнейший ввод невозможен.
class InputClosedException : public InputException {
public:
    explicit InputClosedException(const std::string& message);
};

#endif
