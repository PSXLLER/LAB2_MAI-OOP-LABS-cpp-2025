#pragma once
#include "Array.h"
#include <string>
#include <iostream>
using std::string;
using std::ostream;

class Hex {
    Array digits;
    static unsigned char toVal(char c);
    static char toChr(unsigned char v);
public:
    Hex();
    Hex(const Hex& h);
    Hex(Hex&& h) noexcept;
    explicit Hex(const string& s);
    Hex(std::initializer_list<unsigned char> t);
    explicit Hex(const Array& a);
    ~Hex() noexcept;

    Hex& operator=(const Hex& other);
    Hex& operator=(Hex&& other) noexcept;
    size_t size() const;
    string toString() const;
    Hex add(const Hex& h) const;
    Hex sub(const Hex& h) const;
    Hex copy() const;
    bool eq(const Hex& h) const;
    bool less(const Hex& h) const;
    bool greater(const Hex& h) const;
    void print(ostream& os = std::cout) const;
    void add_a(const Hex& h);
    void sub_a(const Hex& h);
    void copy_a(const Hex& h);
};
