#pragma once
#include <string>
#include <vector>
#include <map>

namespace pi {
    namespace code {
        class Code {
            public:
                enum Opcode {
                    OP_LOAD = 0,
                    OP_ADD,
                    OP_SUB,
                    OP_MUL,
                    OP_DIV,
                    OP_POP
                };
                Code()=default;
                ~Code()=default;

                static Code& lookup(Opcode op);
            public:
                std::string m_name;
                std::vector<int> m_operand_widths;
                static std::map<Opcode, Code> m_codes;
        };
    }
}