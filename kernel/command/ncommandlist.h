//
// Created by EgrZver on 04.07.2023.
//
#include <kernel/command/ncommands.h>
#include <kernel/storage/nmachinememory.h>

#ifndef NERVI_NCOMMANDLISTS_H
#define NERVI_NCOMMANDLISTS_H

namespace NerviKernel {
    int (*NerviCoreCommands[1]) (NVirtualMachineStorage*, long long, long long) = {
        byteAnd
    };
}

#endif //NERVI_NCOMMANDLISTS_H
