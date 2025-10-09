#pragma once

#include "Array.h"
#include <iostream>
#include <string>

using std::invalid_argument;
using std::ostream;
using std::cout;
using std::string;

class Hex
{
    private:
    Array digits;

    static unsigned char CharToHex(char c);
    static char HexToChar(unsigned char v);

    public:
    Hex();
    Hex(const Hex& other);
    Hex(Hex&& other) noexcept;
    explicit Hex(const string& str);
    Hex(const initializer_list<unsigned char>& t);
    explicit Hex(const Array& arr);
    ~Hex() noexcept;

    size_t size() const;
    string toString() const;
    Hex add(const Hex& other) const;
    Hex sub(const Hex& other) const;
    Hex copy() const;
    bool equal(const Hex& other) const;
    bool less(const Hex& other) const;
    bool greater(const Hex& other) const;
    void print(ostream& os = cout) const;
    void add_a(const Hex& other);
    void sub_a(const Hex& other);
    void copy_a(const Hex& other);
};