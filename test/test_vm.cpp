#include "src/code/instruction.h"
#include <iostream>
using namespace pi::code;

int main() {
    Instruction ins;
    ins.make(Code::OP_LOAD, {1});
    std::cout<<ins.str()<<std::endl;
    Instruction ins2;
    ins2.make(Code::OP_ADD);
    std::cout<<ins2.str()<<std::endl;
    return 0;
}