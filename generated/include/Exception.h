#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

class BaseException : public std::exception {
protected:
    std::string message;

public:
    explicit BaseException(const std::string &msg) {
        this->message = msg;
    }

    const char *what() const noexcept override {
        return message.c_str();
    }
};

class FileNotFoundException : public BaseException {
public:
    explicit FileNotFoundException(const std::string &filename)
        : BaseException("File not found: " + filename + '\n') {
    }
};


class PlayerException : public BaseException {
public:
    explicit PlayerException(const std::string &details)
        : BaseException("Invalid input for player " + details + '\n') {
    }
};


class SpecialPropertyPlacementException : public BaseException {
public:
    SpecialPropertyPlacementException(const int index, const std::string &propertyName)
        : BaseException(
            "Special property '" + propertyName + "' placed incorrectly at index " + std::to_string(index) + '\n') {
    }
};

#endif //EXCEPTION_H
