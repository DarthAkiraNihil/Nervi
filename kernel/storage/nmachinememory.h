/**
 * \file machinememory.h
 * \brief TEST TEST TEST
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
        void pushToStack(char value);
        void pushReturnAddress(long long address);
        char popFromStack();
        long long popReturn();
        void returnJump();
        void jump(long long destination);
    };

    /**
     * \brief The NVirtualMachineStorage constructor that creates a null-determined storage device.
     * \details Initializes storage's memory array with the defined size and initializes its cells with zeros
     * \param size The size of storage array in bytes. Max is 2^64 - 1 bytes
     */
    NVirtualMachineStorage::NVirtualMachineStorage(long long size): NMemoryCard(size) {
        memset(this->registers.CHAR_REGS, 0, 27);
        this->registers.IP = 0;
    }

    /**
     * \brief The NVirtualMachineStorage destructor that releases all its used resources.
     * \details Deletes all storage array data that have been reserved by creating an object of the class, clears the list of the locked addresses and defines its size as 0
     */
    NVirtualMachineStorage::~NVirtualMachineStorage() {
        delete[] this->storage;
        this->size = 0;
        this->locked.clear();
    }


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

    char NVirtualMachineStorage::getRegister(NerviKernel::NRegisterNames registerName) {
        if (registerName > 27) {
            throw NerviInternalExceptions::InvalidRegisterException(fmt::format("Invalid required register index: {}", int(registerName)));
        }
        else {
            if (registerName == IP) {
                throw NerviInternalExceptions::InstructionPointerInterruptionPushException("Trying to push a value into IP with the method pushToRegister has no sense due the difference between char and long long types");
            } else {
                return this->registers.CHAR_REGS[registerName];
            }
        }
    }
    void NVirtualMachineStorage::pushToStack(char value) {
        this->stack.push(value);
    }
    void NVirtualMachineStorage::pushReturnAddress(long long address) {
        this->retStack.push(address);
    }
    char NVirtualMachineStorage::popFromStack() {
        return this->stack.top();
    }
    long long NVirtualMachineStorage::popReturn() {

    }
    void NVirtualMachineStorage::returnJump() {

    }
    void NVirtualMachineStorage::jump(long long destination) {

    }
}


#endif