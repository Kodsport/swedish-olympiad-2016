#pragma once
#include <string>
enum InstructionType
{
    gotoblocked,
    forward,
    rotate_left,
    rotate_right,
    loop,
    endloop,
    call,
    ret,
    label,
    noop,
    eof
};

struct Instruction
{
    InstructionType type;
    std::string name;
    int target;
    int num_iterations;

    Instruction(InstructionType type) : type(type), target(-10), name("no_label") {}
    Instruction(InstructionType type, std::string name) : type(type), name(name) {}
    Instruction(InstructionType type, int number) : type(type)
    {
        if (type == loop) num_iterations = number;
        else target = number;
    }
    Instruction() : type(noop), target(-10) {}
};
