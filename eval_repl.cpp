#include "src/evaluator/evaluator.h"
#include "src/parser/parser.h"
#include "src/lexer/lexer.h"
#include <cstdio>

using namespace pi::evaluator;
using namespace pi::parser;
using namespace pi::lexer;

const std::string prompt = "<< ";

int main() {
    std::cout<<"Welcome to the PI programming language!\n";
    std::shared_ptr<Evaluator> evaluator = std::shared_ptr<Evaluator>(new Evaluator());
    while (true) {
        std::cout << prompt;
        std::string text;
        std::getline(std::cin, text);
        if (text == "exit") {
            std::cout << "Bye!\n";
            break;
        }
        std::shared_ptr<Lexer> lexer = std::shared_ptr<Lexer>(new Lexer(text.c_str(),text.size()));
        std::shared_ptr<Parser> parser = std::shared_ptr<Parser>(new Parser(lexer));
        auto program = parser->parse_program();
        auto errors = parser->errors();
        if (!errors.empty()) {
            for (auto &e : errors) {
                std::cout << e << std::endl;
            }
            continue;;
        }
        auto evaluated = evaluator->eval(program);
        if (evaluated) {
            std::cout << evaluated->str() << std::endl;
        }
    }
    return 0;
}