//
// Created by EgrZver on 30.06.2023.
//
#include <iostream>

#ifndef NERVI_NTOKENS_H
#define NERVI_NTOKENS_H

/**
 * \brief A structure to store Nervi command arguments in a raw view (as strings)
 * \details Represents a structure that stores an advanced memory address with disc number and these and address in the disc
 * but these are written as strings. This is used in command composing
 */
struct NRawMemoryAddress {
    std::string rDiscNumber, rAddress;
};

/**
 * \brief A structure to store Nervi command arguments but as strings
 * \details The structure can store an advanced memory address or a char value but written as a string. This is used in command composing
 */
struct NRawCommandArgument {
    NRawMemoryAddress rArgAddress;
    std::string rArgData;
};

/**
 * \brief A structure to represent tokens of Nervi command
 * \details Stores the string representation of the number of a command presented by its plugin index and its own index (number in the plugin's command list) and two NRawCommandArguments
 */
struct NCommandTokens {
    std::string rPluginIndex, rCommandIndex;
    NRawMemoryAddress fArg, sArg;
};

#endif //NERVI_NTOKENS_H
