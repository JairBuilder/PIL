#include "./src/parser/parser.h"
#include <memory>
using namespace pi::parser;

#include "./src/lexer/lexer.h"
using namespace pi::lexer;

int main() {
    std::shared_ptr<Lexer> lexer(new Lexer("./test/code.pi"));
    std::shared_ptr<Parser> parser(new Parser(lexer));
    auto program = parser->parse_program();
    program->show();
    return 0;
}