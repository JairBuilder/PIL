#include "src/evaluator/evaluator.h"
#include "src/parser/parser.h"
#include "src/lexer/lexer.h"
#include <memory>

using namespace pi::evaluator;
using namespace pi::parser;
using namespace pi::lexer;

int main() {
    std::shared_ptr<Lexer> lexer = std::shared_ptr<Lexer>(new Lexer("./test/code.pi"));
    std::shared_ptr<Parser> parser = std::shared_ptr<Parser>(new Parser(lexer));
    auto program = parser->parse_program();
    auto errors = parser->errors();
    if (!errors.empty()) {
        for (auto &e : errors) {
            std::cout << e << std::endl;
        }
        return -1;
    }
    std::shared_ptr<Evaluator> evaluator = std::shared_ptr<Evaluator>(new Evaluator());
    auto evaluated = evaluator->eval(program);
    if (evaluated) {
        std::cout << evaluated->str() << std::endl;
    }
    return 0;
}