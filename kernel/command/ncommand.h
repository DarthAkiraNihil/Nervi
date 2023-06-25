//
// Created by EgrZver on 25.06.2023.
//

#ifndef NERVI_NCOMMAND_H
#define NERVI_NCOMMAND_H

struct NMemoryAddress {
    short discNumber;
    long long address;
};

struct NCommandArgument {
    NMemoryAddress argAddress;
    char argData;
};

struct NCommand {
    int pluginIndex, commandIndex;
    NCommandArgument fArg, sArg;
};

#endif //NERVI_NCOMMAND_H
