#pragma once
#include <map>
#include <memory>
#include <string>

namespace pi {
    namespace object {
        class Object {
        public:
            enum Type {
                OBJECT_ERROR=0,
                OBJECT_INTEGER
            };
            virtual ~Object() {}
            Object(Type type) : m_type(type) {}
            Object() {}
            
            Type type() const { return m_type; }
            std::string name() const;
            virtual std::string str() const = 0;

            static std::shared_ptr<Object> new_error(const char * format, ...);
            static std::shared_ptr<Object> new_integer(int64_t value);
            
        protected:
            Type m_type;
            static std::map<Type, std::string> m_names;
        };
    }
}