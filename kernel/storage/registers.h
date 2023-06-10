//
// Created by EgrZver on 08.06.2023.
//

#ifndef NERVI_REGISTERS_H
#define NERVI_REGISTERS_H
namespace Nervi {

    struct NRegisters {
        char CHAR_REGS[26];
        long long IP;
        char LASTINTR;
    };

}
#endif //NERVI_REGISTERS_H
