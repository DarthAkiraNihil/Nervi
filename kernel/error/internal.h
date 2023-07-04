//
// Created by EgrZver on 07.06.2023.
//
#include <iostream>

#ifndef NERVI_LOCAL_H
#define NERVI_LOCAL_H

namespace NerviInternalExceptions {


    /**
    * \brief Represents the class of the exception caused by addressing an invalid cell
    * \details This is the class of the exception that is thrown if a cell with an invalid index has been addressed.
    * The invalid indexes are any below zero or any greater than the size of a memory device (i.e. NMemoryCard or NVirtualMachineStorage)
    * These methods throw the exception:
    * todo doc these
    */
    class InvalidIndexException : public std::exception {
    private:
        std::string message_;
    public:
        explicit InvalidIndexException(const std::string &message);

        const char *what() const noexcept override { return message_.c_str(); }
    };

    /**
    * \brief Represents the class of the exception caused by addressing a locked cell
    * \details This is the class of the exception that is thrown if a locked cell has been addressed.
    * The throwing happens when you try to set a value of a cell that you have been locked before the setting.
    */
    class LockedAddressException : public std::exception {
    private:
        std::string message_;
    public:
        explicit LockedAddressException(const std::string &message);

        const char *what() const noexcept override { return message_.c_str(); }
    };

    /**
    * \brief Represents the class of the exception caused by addressing an non-existent register
    * \details This is the class of the exception that is thrown if the number of register you are trying to push a value into represent an unknown register
    * The number of registers is declared in the enumeration NerviKernel::NRegisterNames and the indexes of them are between 0 and 28 includely
    * \warning The exception is not thrown if you are trying to push a value into the IP
    */
    class InvalidRegisterException : public std::exception {
    private:
        std::string message_;
    public:
        explicit InvalidRegisterException(const std::string &message);

        const char *what() const noexcept override { return message_.c_str(); }
    };

    /**
    * \brief Represents the class of the exception caused by addressing the IP in the methods pushToRegister and getRegister
    * \details This is the class of the exception that is thrown if you are trying to address the IP in the methods pushToRegister and getRegister.
     *This has no sense due the difference between char and long long types, use getIP, jump, jumpNext or returnJump instead
    */
    class InstructionPointerInterruptionPushException : public std::exception {
    private:
        std::string message_;
    public:
        explicit InstructionPointerInterruptionPushException(const std::string &message);

        const char *what() const noexcept override { return message_.c_str(); }
    };

    /**
    * \brief Represents the class of the exception that is used only for testing
    * \details This is the class of the exception that is thrown in any situation that is needed by a tester of a developer.
    * \warning Do not use this exception in the kernel headers because this exception is not for general functionality, just for testing
    */
    class DeveloperTestException : public std::exception {
    private:
        std::string message_;
    public:
        explicit DeveloperTestException(const std::string &message);

        const char *what() const noexcept override { return message_.c_str(); }
    };

    InstructionPointerInterruptionPushException::InstructionPointerInterruptionPushException(const std::string &message) : message_(message) {}

    LockedAddressException::LockedAddressException(const std::string &message) : message_(message) {}

    InvalidIndexException::InvalidIndexException(const std::string &message) : message_(message) {}

    InvalidRegisterException::InvalidRegisterException(const std::string &message) : message_(message) {}

    DeveloperTestException::DeveloperTestException(const std::string &message) : message_(message) {}

}
#endif //NERVI_LOCAL_H
