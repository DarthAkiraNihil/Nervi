//
// Created by EgrZver on 04.07.2023.
//
#include <iostream>
#include <kernel/command/ncommands.h>
#include <kernel/storage/nmachinememory.h>

#ifndef NERVI_NCOMMANDLISTS_H
#define NERVI_NCOMMANDLISTS_H

namespace NerviKernel {
    int (*NerviCoreCommands[8]) (NVirtualMachineStorage*, long long, long long) = {
        NerviCoreCommandsDeclaration::byteAnd,
        NerviCoreCommandsDeclaration::byteOr,
        NerviCoreCommandsDeclaration::byteNot,
        NerviCoreCommandsDeclaration::byteXor,
        NerviCoreCommandsDeclaration::byteEqv,
        NerviCoreCommandsDeclaration::byteImp,
        NerviCoreCommandsDeclaration::byteNand,
        NerviCoreCommandsDeclaration::byteNor
    };
    std::string NerviCoreCommandsNames[8] = {
        "and",
        "or",
        "not",
        "xor",
        "eqv",
        "imp",
        "nand",
        "nor"
    };
}

#endif //NERVI_NCOMMANDLISTS_H
