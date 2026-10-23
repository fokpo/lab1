#include "Exceptions.h"

FigureException::FigureException(const std::string& message) : std::runtime_error(message) {}
InvalidValueException::InvalidValueException(const std::string& message) : FigureException(message) {}
InvalidTypeException::InvalidTypeException(const std::string& message) : FigureException(message) {}
IndexOutOfRangeException::IndexOutOfRangeException(const std::string& message) : FigureException(message) {}
FileException::FileException(const std::string& message) : FigureException(message) {}
InputException::InputException(const std::string& message) : FigureException(message) {}
InputClosedException::InputClosedException(const std::string& message) : InputException(message) {}
