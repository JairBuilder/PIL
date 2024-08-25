#include "instruction.h"
#include <cstdint>
#include <cstring>
#include <endian.h>
#include <algorithm>
#include <sstream>
#include <string>
using namespace pi::code;

Instruction::Instruction() {
    m_byteorder = byteorder();
}

bool Instruction::make(Code::Opcode op, const std::vector<int>& operands) {
    auto& def = Code::lookup(op);
    int len = 1;
    for (auto width : def.m_operand_widths) {
        len += width;
    }
    m_data.reserve(len);

    write(uint8_t(op));
    for (auto i=0;i<def.m_operand_widths.size();i++) {
        auto width = def.m_operand_widths[i];
        switch (width) {
            case 1: {
                write(uint8_t(operands[i]));
                break;
            }
            case 2: {
                write(uint16_t(operands[i]));
                break;
            }
            default:
                break;
        }
    }
    return true;
}

Instruction::ByteOrder Instruction::byteorder() {
    int n = 0x12345678;
    char str[4] = {0};
    memcpy(str, &n, 4);
    if (str[0] == 0x12) {
        return BigEndian;
    } 
    else {
        return LittleEndian;
    }
}

void Instruction::write(const char* data, size_t len) {
    int size = m_data.size();
    m_data.resize(size + len);
    std::memcpy(&m_data[size], data, len);
}

bool Instruction::read(char* data, size_t len) {
    std::memcpy(data, (char*)&m_data[m_offset], len);
    m_offset += len;
    return true;
}

void Instruction::write(uint8_t val) {
    write((char*)&val, 1);
}

void Instruction::write(uint16_t val) {
    if (m_byteorder == BigEndian) {
        char* first = (char*)&val;
        char* last = (char*)&val + sizeof(uint16_t);
        std::reverse(first, last);
    }
    write((char*)&val, sizeof(uint16_t));
}

bool Instruction::read(uint8_t& val) {
    val = m_data[m_offset];
    m_offset += 1;
    return true;
}

bool Instruction::read(uint16_t& val) {
    val = *(int16_t *)(&m_data[m_offset]);
    if (m_byteorder == BigEndian) {
        char * first = (char *)&val;
        char * last = (char *)&val + sizeof(uint16_t);
        std::reverse(first, last);
    }
    m_offset += 2;
    return true;
}

Code::Opcode Instruction::opcode() {
    m_offset = 0;
    uint8_t op;
    read(op);
    return Code::Opcode(op);
}

int Instruction::size() const {
    return (int)m_data.size();
}

std::string Instruction::str() {
    std::ostringstream oss;
    m_offset = 0;
    uint8_t op;
    read(op);
    auto &def = Code::lookup(Code::Opcode(op));
    oss << def.m_name;
    for (int i=0;i<def.m_operand_widths.size();i++) {
        auto width = def.m_operand_widths[i];
        switch (width) {
            case 1: {
                uint8_t val;
                read(val);
                oss << " " << int(val);
                break;
            }
            case 2: {
                uint16_t val;
                read(val);
                oss << " " << int(val);
                break;
            }
            default:
                break;
        }
    }
    return oss.str();
}