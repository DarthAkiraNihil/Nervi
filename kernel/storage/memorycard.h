#include <list>
#include <kernel/error/internal.h>
#include <fmt/core.h>

#ifndef KERNEL_STORAGE_NMEMC
#define KERNEL_STORAGE_NMEMC

namespace NerviKernel {

    /**
     * \brief A class of a memory card that only stores values in an array
     * \details This is the class that stores some amount of chars in an array that defines during the class' construction.
     * The size of an array is immutable and the class does not provide a possibility to change it.
     * The class objects cannot be assigned to other class objects. The following code will cause an error:
     * \code
     * NerviKernel::NMemoryCard card1(4);
     * NerviKernel::NMemoryCard card2 = card1; //error
     * \endcode
     * Also provides an opportunity to protect the array's cells from writing (i.e. locking), the indexes of the locked are stored in a list.
     * The locked cells are available only for reading, but can be unlocked from write-locking
     */

    class NMemoryCard {
        NMemoryCard(const NMemoryCard& nmc) = delete;
        NMemoryCard& operator=(const NMemoryCard& nmc) = delete;
        private:
            char *storage;
            long long size;
            std::list<long long> locked;
            bool isLocked(long long index);
        public:
            explicit NMemoryCard(long long size);
            ~NMemoryCard();
            void lockCell(long long index);
            void unlockCell(long long index);
            long long getSize();
            void setValueAt(long long index, char value);
            char getValueAt(long long index);
    };

    bool NMemoryCard::isLocked(long long index) {
        if (index < 0 || index > this->size - 1) {
            throw NerviInternalExceptions::InvalidIndexException(fmt::format("Invalid required index: {} (expected positive and less than {})", index, this->size));
        }
        else {
            for (auto iterator = this->locked.cbegin(); iterator != this->locked.cend(); iterator++) {
                if (*iterator == index) {
                    return true;
                }
            }
            return false;
        }
    }

    /**
     * \brief The NMemoryCard constructor that initializes memory array
     * \details Creates an array with desired length and fills it with zero values
     * \param size The size of storage array in bytes. Max is 2^64 - 1 bytes (long long max value)
     */
    NMemoryCard::NMemoryCard(long long size) {
        this->size = size;
        this->storage = new char[size];
        memset(this->storage, 0, size);
    }

    /**
     * \brief The NMemoryCard de that releases all its used resources.
     * \details Deletes all storage array data that have been reserved by creating an object of the class, clears the list of the locked addresses and defines its size as 0
     */
    NMemoryCard::~NMemoryCard() {
        delete[] this->storage;
        this->size = 0;
        this->locked.clear();
    }

    /**
     * \brief Sets a storage cell's status as write-locked. It pushes back the index to the list of the locked
     * \param index The address of a cell to lock
     * \throw InvalidIndexException If the index is out of bounds of the storage array
     */
    void NMemoryCard::lockCell(long long index) {
        if (index < 0 || index > this->size - 1) {
            throw NerviInternalExceptions::InvalidIndexException(fmt::format("Invalid required index to block: {} (expected positive and less than {})", index, this->size));
        }
        else {
            this->locked.push_back(index);
        }
    }

    /**
     * \brief Unlocks a storage cell from write-protection
     * \details Unlocks a storage cell from write-protection. It erases the cell to unlock from the list of the locked,
     * but if the required cell is not locked nothing happens
     * \param index The address of an cell to unlock
     * \throw InvalidIndexException If the index is out of bounds of the storage array
     */
    void NMemoryCard::unlockCell(long long index) {
        if (index < 0 || index > this->size - 1) {
            throw NerviInternalExceptions::InvalidIndexException(fmt::format("Invalid required index to block: {} (expected positive and less than {})", index, this->size));
        }
        else {
            for (auto iterator = this->locked.cbegin(); iterator != this->locked.cend(); iterator++) {
                if (*iterator == index) {
                    this->locked.erase(iterator);
                    break;
                }
            }
        }
    }

    /**
     * \brief Returns the size of the storage
     * \return The size of the storage
     */
    long long NMemoryCard::getSize() {
        return this->size;
    }

    /**
     * \brief Writes a value to the cell of the storage at desired index.
     * \param index The address of destination
     * \param value The value to write
     * \throw InvalidIndexException If the index is out of bounds of the storage array
     * \throw LockedAddressException If selected cell is write-locked
     */
    void NMemoryCard::setValueAt(long long index, char value) {
        if (index < 0 || index > this->size) {
            throw NerviInternalExceptions::InvalidIndexException(fmt::format("Invalid required index: {} (expected positive and less than {})", index, this->size));
        } else if (!(this->isLocked(index))) {
            this->storage[index] = value;
        } else {
            //std::runtime_error("The required address is write-locked");
            throw NerviInternalExceptions::LockedAddressException(fmt::format("Memory cell with the address {} is write-locked!", index));
        }
    }

    /**
     * Returns a value of a cell of the storage at desired index
     * @param index The address of a cell to get value
     * @return The value of selected cell
     * \throw InvalidIndexException If the index is out of bounds of the storage array
     */
    char NMemoryCard::getValueAt(long long index) {
        if (index < 0 || index > this->size) {
            throw NerviInternalExceptions::InvalidIndexException(fmt::format("Invalid required index: {} (expected positive and less than {})", index, this->size));
        } else {
            return this->storage[index];
        }
    }
}

#endif