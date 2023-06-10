//
// Created by EgrZver on 07.06.2023.
//
#include <iostream>

#ifndef NERVI_LOCAL_H
#define NERVI_LOCAL_H

namespace NerviInternalExceptions {

    class InvalidIndexException : public std::exception {
    private:
        std::string message_;
    public:
        explicit InvalidIndexException(const std::string &message);

        const char *what() const noexcept override { return message_.c_str(); }
    };

    class LockedAddressException : public std::exception {
    private:
        std::string message_;
    public:
        explicit LockedAddressException(const std::string &message);

        const char *what() const noexcept override { return message_.c_str(); }
    };

    class InvalidRegisterException : public std::exception {
    private:
        std::string message_;
    public:
        explicit InvalidRegisterException(const std::string &message);

        const char *what() const noexcept override { return message_.c_str(); }
    };

    class InstructionPointerInterruptionPushException : public std::exception {
    private:
        std::string message_;
    public:
        explicit InstructionPointerInterruptionPushException(const std::string &message);

        const char *what() const noexcept override { return message_.c_str(); }
    };

    InstructionPointerInterruptionPushException::InstructionPointerInterruptionPushException(const std::string &message) : message_(message) {}

    LockedAddressException::LockedAddressException(const std::string &message) : message_(message) {}

    InvalidIndexException::InvalidIndexException(const std::string &message) : message_(message) {}

    InvalidRegisterException::InvalidRegisterException(const std::string &message) : message_(message) {}

}
#endif //NERVI_LOCAL_H
