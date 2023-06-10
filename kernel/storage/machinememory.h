#include <memory.h>
#include <list>
#include <kernel/error/local.h>
#include <kernel/storage/registers.h>
#include <kernel/constant/regadresses.h>
#include <stdexcept>
#include <fmt/core.h>

#ifndef KERNEL_STORAGE_NMEM
#define KERNEL_STORAGE_NMEM


/**
 * \brief The Main namespace of the library
 * \details Represents the namespace which contains all the classes, structs and methods of Nervi Kernel
 */

namespace Nervi {

    /**
    * \brief Represents the class of an internal memory device of a virtual machine
    * \details The class is for storing char values in an array, whose size is immutable and limited my the max value of the type long long.
    * Also provides an opportunity to protect cells from writing (i.e. locking), the indexes of th locked are stored in a list
    */
    class NVirtualMachineStorage {
    private:
        char *storage;
        long long size;
        std::list<long long> locked;
        NRegisters registers;
        bool isLocked(long long index);
    public:
        explicit NVirtualMachineStorage(long long size);
        ~NVirtualMachineStorage();
        void lockCell(long long index);
        void unlockCell(long long index);
        long long getSize();
        void setValueAt(long long index, char value);
        char getValueAt(long long index);
        void pushToRegister(Nervi::NRegisterNames registerName, char value);
    };

    bool NVirtualMachineStorage::isLocked(long long index) {
        for (auto iterator = this->locked.cbegin(); iterator != this->locked.cend(); iterator++) {
            if (*iterator == index) {
                return true;
            }
        }
        return false;
        //todo error if no cell found
    }

/**
 * \brief The NVirtualMachineStorage constructor that creates a null-determined storage device.
 * Initializes storage's memory array with the defined size and writes to its cells zeros
 * \param size The size of storage array in bytes. Max is 9 223 372 036 854 775 807 bytes
 */
    NVirtualMachineStorage::NVirtualMachineStorage(long long size) {
        this->size = size;
        this->storage = new char[size];
        memset(this->storage, 0, size);
    }

/**
 * \brief The NVirtualMachineStorage destructor that released all its used resources.
 * Deletes all storage array data that have been reserved by creating an object of the class, clears the list of the locked addresses and defines its size as 0
 */
    NVirtualMachineStorage::~NVirtualMachineStorage() {
        delete[] this->storage;
        this->size = 0;
        this->locked.clear();
    }

/**
 * \brief Sets a storage cell's status as write-locked. It pushes back the index to the list of the locked
 * @param index The address of a lockable cell
 */
    void NVirtualMachineStorage::lockCell(long long index) {
        this->locked.push_back(index);
        //todo no action if locked
    }

/**
 * \brief Unlocks a storage cell from write-protection. It erases the unlockable adress from the list of the locked
 * @param index The address of an unlockable cell
 */
    void NVirtualMachineStorage::unlockCell(long long index) {
        //todo no action if not locked
        for (auto iterator = this->locked.cbegin(); iterator != this->locked.cend(); iterator++) {
            if (*iterator == index) {
                this->locked.erase(iterator);
                break;
            }
        }
    }

/**
 * Returns the size of the storage
 * @return The size of the storage
 */
    long long NVirtualMachineStorage::getSize() {
        return this->size;
    }

/**
 * Writes a value to the cell of the storage at desired index.
 * @param index The adress of destination
 * \param value The value to write
 * \throw InvalidIndexException If the index is out of bounds of the storage array
 * \throw LockedAdressException If selected cell is write-locked
 */
    void NVirtualMachineStorage::setValueAt(long long index, char value) {
        if (index < 0 || index > this->size) {
            throw InvalidIndexException(fmt::format("Invalid required index: {} (expected positive and less than {})", index, this->size));
        } else if (!(this->isLocked(index))) {
            this->storage[index] = value;
        } else {
            //std::runtime_error("The required adress is write-locked");
            throw LockedAdressException(fmt::format("Memory cell with the address {} is write-locked!", index));
        }
    }

/**
 * Returns a value of a cell of the storage at desired index
 * @param index The address of a cell to get value
 * @return The value of selected cell
 * \throw InvalidIndexException If the index is out of bounds of the storage array
 */
    char NVirtualMachineStorage::getValueAt(long long index) {
        if (index < 0 || index > this->size) {
            throw InvalidIndexException(fmt::format("Invalid required index: {} (expected positive and less than {})", index, this->size));
        } else {
            return this->storage[index];
        }
    }

    void NVirtualMachineStorage::pushToRegister(Nervi::NRegisterNames registerName, char value) {
        if (registerName > 27) {
            //throw
        }
        else {
            switch (registerName) {
                case IP: {
                    //throw...
                    break;
                }
                case LASTINTR: {
                    this->registers.LASTINTR = value;
                    break;
                }
                default: {
                    this->registers.CHAR_REGS[registerName] = value;
                }
            }
        }
    }

}


#endif