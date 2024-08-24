#include "evaluator.h"
#include "src/object/object.h"
#include <memory>
using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_program(const std::list<std::shared_ptr<ast::Statement>>& stmts) {
    std::shared_ptr<Object> result;
    for (auto stmt : stmts) {
        result = eval(stmt);
        if (is_error(result)) {
            break;
        }
    }
    return result;
}