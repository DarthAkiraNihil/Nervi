//
// Created by EgrZver on 30.06.2023.
//
#include <kernel/storage/nmachinememory.h>


#ifndef NERVI_NCOMMANDLIST_H
#define NERVI_NCOMMANDLIST_H

namespace NerviKernel {
    namespace NerviCoreCommandsDeclaration {
        int byteAnd(NVirtualMachineStorage* storage, long long first, long long second) {
            storage->setValueAt(first, storage->getValueAt(first) & storage->getValueAt(second));
        }

        int byteOr(NVirtualMachineStorage* storage, long long first, long long second) {
            storage->setValueAt(first, storage->getValueAt(first) | storage->getValueAt(second));
        }

        int byteNot(NVirtualMachineStorage* storage, long long first, long long second) {
            storage->setValueAt(first, ~storage->getValueAt(first));
        }

        int byteXor(NVirtualMachineStorage* storage, long long first, long long second) {
            storage->setValueAt(first, storage->getValueAt(first) ^ storage->getValueAt(second));
        }

        int byteEqv(NVirtualMachineStorage* storage, long long first, long long second) {
            byteXor(storage, first, second);
            byteNot(storage, first, second);
        }

        int byteImp(NVirtualMachineStorage* storage, long long first, long long second) {
            byteNot(storage, first, second);
            byteOr(storage, first, second);
        }

        int byteNand(NVirtualMachineStorage* storage, long long first, long long second) {
            byteAnd(storage, first, second);
            byteNot(storage, first, second);
        }

        int byteNor(NVirtualMachineStorage* storage, long long first, long long second) {
            byteOr(storage, first, second);
            byteNot(storage, first, second);
        }


    }

}

#endif //NERVI_NCOMMANDLIST_H
