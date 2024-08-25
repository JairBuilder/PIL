#pragma once
#include "src/code/instruction.h"
#include "src/compiler/compiler.h"
#include "src/object/object.h"
#include <memory>
#include <vector>
using namespace pi::compiler;

namespace pi {
    namespace vm {
        const int MAX_GLOBAL_SIZE = 65536;
        class VM {
        public:
            VM();
            ~VM()=default;

            void run();
            void push(const std::shared_ptr<Object> &obj);
            void push_integer(int64_t val);
            void push_error(const char* format, ...);
            std::shared_ptr<Object> pop();
            std::shared_ptr<Object> last_pop();
            bool is_error(const std::shared_ptr<Object> &obj);
            void run_binary_operation(Code::Opcode op);
            void run_binary_integer_operation(Code::Opcode op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right);

            void show();

        public:
            std::vector<std::shared_ptr<Object>> m_stack;
            std::vector<std::shared_ptr<Object>> m_globals;
            std::vector<std::shared_ptr<Object>> m_constants;
            std::vector<std::shared_ptr<Instruction>> m_instructions;
            std::shared_ptr<Object> m_last_pop;
            int m_ip; // instruction pointer
        };
    }
}