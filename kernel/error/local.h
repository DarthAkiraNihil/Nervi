//
// Created by EgrZver on 07.06.2023.
//
#include <iostream>

#ifndef NERVI_LOCAL_H
#define NERVI_LOCAL_H

class InvalidIndexException: public std::exception {
private:
    std::string message_;
public:
    explicit InvalidIndexException(const std::string& message);
    const char* what() const noexcept override {
        return message_.c_str();
    }
};

class LockedAdressException: public std::exception {
private:
    std::string message_;
public:
    explicit LockedAdressException(const std::string& message);
    const char* what() const noexcept override {
        return message_.c_str();
    }
};


LockedAdressException::LockedAdressException(const std::string& message) : message_(message) {}
InvalidIndexException::InvalidIndexException(const std::string& message) : message_(message) {}

#endif //NERVI_LOCAL_H
