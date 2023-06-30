//
// Created by EgrZver on 25.06.2023.
//

#ifndef NERVI_NCOMMAND_H
#define NERVI_NCOMMAND_H

namespace NerviKernel {
/**
 * \brief An advanced structure to store a memory address
 * \details Represents a structure that stores an advanced memory address with disc number and the and address in the disc
 */
    struct NMemoryAddress {
        short discNumber;
        long long address;
    };

/**
 * \brief A structure to store Nervi command arguments
 * \details The structure can store an advanced memory address or a char value
 */
    struct NCommandArgument {
        NMemoryAddress argAddress;
        char argData;
    };

/**
 * \brief A structure to represent a Nervi command
 * \details Stores the number of a command presented by its plugin index and its own index (number in the plugin's command list) and two NCommandArguments
 */
    struct NCommand {
        int pluginIndex, commandIndex;
        NCommandArgument fArg, sArg;
    };
}
#endif //NERVI_NCOMMAND_H
