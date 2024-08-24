#include "object.h"
#include "integer.h"
#include "error.h"
#include <memory>
#include <stdarg.h>

using namespace pi::object;

std::map<Object::Type, std::string> Object::m_names = {
    {OBJECT_ERROR,      "error"},
    {OBJECT_INTEGER,    "integer"}
};

std::string Object::name() const {
    auto it = m_names.find(m_type);
    if (it != m_names.end()) {
        return it->second;
    }
    return "";
}

std::shared_ptr<Object> Object::new_error(const char * format, ...) {
    char buf[1024] = "";
    va_list arg_ptr;
    va_start(arg_ptr, format);
    vsnprintf(buf, sizeof(buf), format, arg_ptr);
    va_end(arg_ptr);
    return std::shared_ptr<Error> (new Error(buf));
}

std::shared_ptr<Object> Object::new_integer(int64_t value) {
    return std::shared_ptr<Integer> (new Integer(value));
}
