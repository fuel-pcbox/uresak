#include "common.h"

struct cpu_register
{
    u64 size;
    enum class type
    {
        INTEGER,
        FLOAT,
        VECTOR_INT,
        VECTOR_FLOAT,
        CONSTANT,
    } type;
    std::string name;
};

struct uop
{
    cpu_register dest;
    std::vector<cpu_register> sources;
    std::string mnemonic;
    enum class type
    {
        ADD,
        SUB,
        MUL,
        DIV,
        MOV,
        AND,
        OR,
        XOR,
        SQRT,
        HLT,
    } type;

    static constexpr u64 FLAG_STEP_OUT = 1;
    static constexpr u64 FLAG_STEP_OVER = 2;
    static constexpr u64 FLAG_NORETURN = 4;
    static constexpr u64 FLAG_INTERRUPTIBLE = 8;

    u64 flags;
    u64 cycles;
};

struct cpu_instruction
{
    u64 length;
    std::vector<u8> bytes;
    std::vector<cpu_register> dests;
    std::vector<cpu_register> sources;
    std::vector<uop> uops;
    std::string mnemonic;

    static constexpr u64 FLAG_STEP_OUT = 1;
    static constexpr u64 FLAG_STEP_OVER = 2;
    static constexpr u64 FLAG_NORETURN = 4;
    static constexpr u64 FLAG_INTERRUPTIBLE = 8;

    u64 flags;
    u64 cycles;

    virtual void run() = 0;
};

struct cpu
{
    virtual void run_instr() = 0;
};