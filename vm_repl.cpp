#include "src/code/instruction.h"
#include <memory>
using namespace pi::code;
#include "src/lexer/lexer.h"
using namespace pi::lexer;
#include "src/parser/parser.h"
using namespace pi::parser;
#include "src/compiler/compiler.h"
using namespace pi::compiler;
#include "src/vm/vm.h"
using namespace pi::vm;

const std::string prompt = "<< ";

int main() {
    std::cout<<"Welcome to the PI programming language!\n";
    while (true) {
        std::cout << prompt;
        std::string text;
        std::getline(std::cin, text);
        if (text == "exit") {
            std::cout << "Bye!\n";
            break;
        }
        try {
            std::shared_ptr<Lexer> lexer(new Lexer(text.c_str(),text.size()));
            std::shared_ptr<Parser> parser(new Parser(lexer));
            auto program = parser->parse_program();
            auto errors = parser->errors();
            if (!errors.empty()) {
                for (auto &e : errors) {
                    std::cout << e << std::endl;
                }
                continue;
            }

            std::shared_ptr<Compiler> compiler(new Compiler());
            compiler->compile(program);

            std::shared_ptr<VM> vm(new VM());
            vm->m_instructions = compiler->m_instructions;
            vm->m_constants = compiler->m_constants;
            vm->run();

            auto obj = vm->last_pop();
            std::cout<<obj->str()<<std::endl;
        }catch (std::exception &e) {
            std::cout<<e.what()<<std::endl;
        }
    }
    return 0;
}