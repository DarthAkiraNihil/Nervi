/**
 * \file nmachinememory.h
 * \brief Contains the definition of the class NVirtualMachineStorage
 * \details Contains the definition of the class NVirtualMachineStorage and the following documentation
 * \version 0.1.0-f02e1d99
 * \author TheSwagVader
 */


#include <memory.h>
#include <list>
#include <stack>
#include <kernel/error/internal.h>
#include <kernel/storage/registers.h>
#include <kernel/constant/regadresses.h>
#include <kernel/storage/memorycard.h>
#include <stdexcept>
#include <fmt/core.h>

#ifndef KERNEL_STORAGE_NMEM
#define KERNEL_STORAGE_NMEM


/**
 * \brief The Main namespace of the library
 * \details Represents the namespace which contains all the classes, structs and methods of Nervi Kernel
 */

namespace NerviKernel {

    /**
    * \brief Represents the class of an internal memory device of a virtual machine
    * \details The class is for storing char values in an array, whose size is immutable and limited my the max value of the type long long.
    * Also provides an opportunity to protect cells from writing (i.e. locking), the indexes of th locked are stored in a list
    */
    class NVirtualMachineStorage final: public NMemoryCard{
    private:
        char *storage;
        long long size;
        std::list<long long> locked;
        NRegisters registers;
        std::stack<char> stack; std::stack<long long> retStack;
    public:
        explicit NVirtualMachineStorage(long long size);
        ~NVirtualMachineStorage();
        //void lockCell(long long index);
        //void unlockCell(long long index);
        //long long getSize();
        //void setValueAt(long long index, char value);
        //char getValueAt(long long index);
        void pushToRegister(NerviKernel::NRegisterNames registerName, char value);
        char getRegister(NerviKernel::NRegisterNames registerName);
        long long getIP();
        void pushToStack(char value);
        void pushReturnAddress(long long address);
        char popStack();
        long long popReturn();
        void returnJump();
        void jump(long long destination);
        void jumpNext();
    };

    /**
     * \brief The NVirtualMachineStorage constructor that creates a null-determined storage device.
     * \details Initializes storage's memory array with the defined size and initializes its cells with zeros
     * \param size The size of storage array in bytes. Max is 2^64 - 1 bytes
     */
    NVirtualMachineStorage::NVirtualMachineStorage(long long size): NMemoryCard(size) {
        memset(this->registers.CHAR_REGS, 0, 27);
        this->registers.IP = 0;
        //this->stack = stack;
    }

    /**
     * \brief The NVirtualMachineStorage destructor that releases all its used resources.
     * \details Deletes all storage array data that have been reserved by creating an object of the class, clears the list of the locked addresses and defines its size as 0
     */
    NVirtualMachineStorage::~NVirtualMachineStorage() = default;

    /**
     * \brief Pushes a value to a common register
     * \details Pushes a value to a register declared in the enumeration NerviKernel::NRegisterName, except IP
     * \warning The method does not push a value to the IP because of type mismatching (long long and char).
     * If all registers had been long long-typed there could have been memory overusing.
     * Also Nervi operates with 8-bit memory cells so else there could have been problems if registers had been long-long typed
     * \param registerName The name of the register from the enumeration NerviKernel::NRegisterName
     * \param value The value to push
     * \throw InvalidRegisterException if invalid register name has been passed
     * \throw InstructionPointerInterruptionPushException if IP has been passed as the register to push to
     */
    void NVirtualMachineStorage::pushToRegister(NerviKernel::NRegisterNames registerName, char value) {
        if (registerName > 27) {
            throw NerviInternalExceptions::InvalidRegisterException(fmt::format("Invalid required register index: {}", int(registerName)));
        }
        else {
            if (registerName == IP) {
                throw NerviInternalExceptions::InstructionPointerInterruptionPushException("Trying to push a value into IP with the method pushToRegister has no sense due the difference between char and long long types");
            } else {
                this->registers.CHAR_REGS[registerName] = value;
            }
        }
    }

    /**
     * \brief Returns the value of a common register
     * \details Returns the value of a register declared in the enumeration NerviKernel::NRegisterName, except IP
     * \warning The method does not return the value of the IP because of type mismatching (long long and char).
     * \param registerName The name of the register of the enumeration NerviKernel::NRegisterName
     * \return The value of a required register
     * \throw InvalidRegisterException if invalid register name has been passed
     * \throw InstructionPointerInterruptionPushException if IP has been passed as the register to push to
     */
    char NVirtualMachineStorage::getRegister(NerviKernel::NRegisterNames registerName) {
        if (registerName > 27) {
            throw NerviInternalExceptions::InvalidRegisterException(fmt::format("Invalid required register index: {}", int(registerName)));
        }
        else {
            if (registerName == IP) {
                throw NerviInternalExceptions::InstructionPointerInterruptionPushException("Trying to return the value of the IP with the method getRegister has no sense due the difference between char and long long types");
            } else {
                return this->registers.CHAR_REGS[registerName];
            }
        }
    }

    /**
     * \brief Returns the value of the IP
     * \details Returns the value of the IP
     * \return The value of the IP
     */
    long long NVirtualMachineStorage::getIP() {
        return this->registers.IP;
    }

    /**
     * \brief Pushes a value to the stack
     * \details Pushes a value to the stack to use it later in a program. The stack has no program limit
     * \param value The value to push
     */
    void NVirtualMachineStorage::pushToStack(char value) {
        this->stack.push(value);
    }

    /**
     * \brief Pushes a value to the return stack
     * \details Pushes a value to the return stack. The values of the stack are used as return addresses. The command 'ret' invokes the method
     * \param address The return address to push
     */
    void NVirtualMachineStorage::pushReturnAddress(long long address) {
        this->retStack.push(address);
    }

    /**
     * \brief Pops the top value of the stack
     * \details Deletes the top value of the stack and returns it as the result of this method
     */
    char NVirtualMachineStorage::popStack() {
        char temp = this->stack.top();
        this->stack.pop();
        return temp;
    }

    /**
     * \brief Pops the top value of the return stack
     * \details Deletes the top value of the return stack and returns it as the result of this method
     */
    long long NVirtualMachineStorage::popReturn() {
        long long temp = this->retStack.top();
        this->retStack.pop();
        return temp;
    }

    /**
     * \brief Jumps to the last return address
     * \details Jumps to another command address by changing the value of the IP causing by which executing of a command with required address (i. e. number)
     */
    void NVirtualMachineStorage::returnJump() {
        this->jump(this->popReturn());
    }

    /**
     * \brief Jumps to a command address
     * \details Jumps to the last return address stored in the return stack. The address is popped after jumping
     */
    void NVirtualMachineStorage::jump(long long destination) {
        this->registers.IP = destination;
    }

    /**
     * \brief Jumps to the next command
     * \details Jumps to the next command by increasing the IP value on 1
     */
    void NVirtualMachineStorage::jumpNext() {
        this->registers.IP++;
    }
}


#endif