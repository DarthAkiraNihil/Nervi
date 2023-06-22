//
// Created by EgrZver on 08.06.2023.
//

#ifndef NERVI_REGADRESSES_H
#define NERVI_REGADRESSES_H

namespace NerviKernel {
    /**
     * \brief The names of memory registers
     * \details Contains the names of all NRegisters that are used as aliases instead of using them directly by the struct.
     * It needs to be used in pushing a value into a register in NVirtualMachineStorage class.
     */
    enum NRegisterNames {
        PUTC, /// The PUTC register for raw output of a char to STDOUT
        GETC, /// The GETC register for raw input of a char from STDIN
        FPUTC, /// The FPUTC register for formatted output of a char to STDOUT. Formatting depends on the values of FPUTC_FLAGS_N registers
        FPUTC_FLAGS_1, /// The 1st register of FPUTC format flags
        FPUTC_FLAGS_2, /// The 2nd register of FPUTC format flags
        FPUTC_FLAGS_3, /// The 3rd register of FPUTC format flags
        FPUTC_FLAGS_4, /// The 4th register of FPUTC format flags
        STDIN, /// The register that stores the number of STDIN device that is used at the moment
        STDOUT, /// The register that stores the number of STDOUT device that is used at the moment
        CMPRES, /// The register of the result of the latest comparison in a program
        EAX, /// The EAX register for common purposes
        EBX, /// The EBX register for common purposes
        ECX, /// The ECX register for common purposes
        EDX, /// The EDX register for common purposes
        EEX, /// The EEX register for common purposes
        EFX, /// The EFX register for common purposes
        FAX, /// The FAX register for common purposes
        FBX, /// The FBX register for common purposes
        FCX, /// The FCX register for common purposes
        FDX, /// The FDX register for common purposes
        FEX, /// The FEX register for common purposes
        FFX, /// The FFX register for common purposes
        EAS, /// The EAS register for common purposes
        EBS, /// The EBS register for common purposes
        EAD, /// The EAD register for common purposes
        EBD, /// The EBD register for common purposes
        LASTINTR, /// The LASTINTR register that stores the number of the last invoked interrupt
        IP /// The IP register of the number of a currently executing command
    };
}

#endif //NERVI_REGADRESSES_H
