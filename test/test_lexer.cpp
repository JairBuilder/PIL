#include "src/lexer/lexer.h"
using namespace pi::lexer;

int main() {
  auto lexer =new Lexer("./test/code.pi");
  while (true) {
    auto token = lexer->next_token();
    if (token.type() == Token::Type::TOKEN_EOF) {
      break;
    }
    token.show();
  }
  return 0;
}