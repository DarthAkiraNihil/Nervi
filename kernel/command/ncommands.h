//
// Created by EgrZver on 30.06.2023.
//
#include <kernel/storage/nmachinememory.h>


#ifndef NERVI_NCOMMANDLIST_H
#define NERVI_NCOMMANDLIST_H

namespace NerviKernel {
    int byteAnd(NVirtualMachineStorage* storage, long long first, long long second) {
        storage->setValueAt(first, storage->getValueAt(first) & storage->getValueAt(second));
    }
}

#endif //NERVI_NCOMMANDLIST_H
