#include "vm.h"
#include "src/code/code.h"
#include "src/object/error.h"
#include "src/object/object.h"
#include "src/evaluator/evaluator.h"
#include <cstdarg>
#include <stdexcept>
using namespace pi::vm;
using namespace pi::code;
VM::VM() {
    m_globals.resize(MAX_GLOBAL_SIZE);
}

void VM::run() {
    while (m_ip<m_instructions.size()) {
        auto ins = m_instructions[m_ip];
        auto op = ins->opcode();
        switch (op) {
            case Code::OP_LOAD : {
                uint16_t val = 0;
                ins->read(val);
                push(m_constants[val]);
                break;
            }
            case Code::OP_POP : {
                pop();
                break;
            }
            case Code::OP_ADD :
            case Code::OP_SUB :
            case Code::OP_MUL :
            case Code::OP_DIV : {
                run_binary_operation(op);
                break;
            }
            default: {
                auto code=Code::lookup(op);
                std::cout<<"operation undefined: opcode: "<<code.m_name<<std::endl;
                break;
            }
        }
        m_ip++;
    }
}

void VM::push(const std::shared_ptr<Object> &obj) {
    m_stack.push_back(obj);
}

void VM::push_integer(int64_t val) {
    push(Object::new_integer(val));
}

void VM::push_error(const char* format, ...) {
    char buf[1024]={0};
    va_list args;
    va_start(args, format);
    vsnprintf(buf, sizeof(buf), format, args);
    va_end(args);

    std::shared_ptr<object::Error> obj(new object::Error());
    obj->m_message=buf;
    push(obj);
}

std::shared_ptr<Object> VM::pop() {
    if (m_stack.empty()) {
        push_error("stack is empty");
        return nullptr;
    }
    auto obj=m_stack.back();
    m_stack.pop_back();
    if (is_error(obj)) {
        throw std::logic_error(obj->str());
    }
    m_last_pop=obj;
    return obj;
}

std::shared_ptr<Object> VM::last_pop() {
    return m_last_pop;
}

bool VM::is_error(const std::shared_ptr<Object> &obj) {
    return obj->type()==Object::OBJECT_ERROR;
}

void VM::show() {
    std::cout<<"globals:"<<std::endl;
    for (int i=0; i<m_globals.size(); i++) {
        if (m_globals[i]) {
            std::cout<<"\t["<<i<<"]"<<m_globals[i]->str()<<std::endl;
        }
    }
    std::cout<<std::endl;
    std::cout<<"stack size: "<<m_stack.size()<<std::endl;
    for (auto obj: m_stack) {
        if (obj) {
            std::cout<<"\t"<<obj->str()<<std::endl;
        }
        else {
            std::cout<<"\tnullptr"<<std::endl;
        }
    }
    std::cout<<std::endl;
}