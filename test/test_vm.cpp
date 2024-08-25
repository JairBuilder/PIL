#include "src/code/instruction.h"
#include <memory>
using namespace pi::code;
#include "src/lexer/lexer.h"
using namespace pi::lexer;
#include "src/parser/parser.h"
using namespace pi::parser;
#include "src/compiler/compiler.h"
using namespace pi::compiler;

int main() {
    std::shared_ptr<Lexer> lexer(new Lexer("./test/code.pi"));
    std::shared_ptr<Parser> parser(new Parser(lexer));
    auto program = parser->parse_program();

    std::shared_ptr<Compiler> compiler(new Compiler());
    compiler->compile(program);
    compiler->show();
    return 0;
}