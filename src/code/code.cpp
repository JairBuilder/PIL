#include "code.h"
#include <map>
#include <stdexcept>
using namespace pi::code;

std::map<Code::Opcode,Code> Code::m_codes {
    {OP_LOAD, {"op_load", {2}}},
    {OP_ADD, {"op_add", {}}},
    {OP_SUB, {"op_sub", {}}},
    {OP_MUL, {"op_mul", {}}},
    {OP_DIV, {"op_div", {}}},
    {OP_POP, {"op_pop", {}}}
};

Code& Code::lookup(Opcode op) {
    auto it = m_codes.find(op);
    if (it == m_codes.end()) {
        throw std::logic_error("opcode undefined: " + std::to_string(op));
    }
    return it->second;
}

