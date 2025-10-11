#pragma once
#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <string>

using std::string;
using std::initializer_list;
using std::out_of_range;
using std::invalid_argument;
using std::ostream;

class Array {
    unsigned char* data;
    size_t len;
public:
    Array();
    Array(size_t n, unsigned char v = 0);
    Array(initializer_list<unsigned char> t);
    Array(const string& s);
    Array(const Array& a);
    Array(Array&& a) noexcept;
    virtual ~Array() noexcept;

    Array& operator=(const Array& a);
    Array& operator=(Array&& a) noexcept;

    size_t size() const;
    unsigned char at(size_t i) const;
    Array add(const Array& other) const;
    Array sub(const Array& other) const;
    bool eq(const Array& other) const;
    bool less(const Array& other) const;
    bool greater(const Array& other) const;
    void set(size_t i, unsigned char v);
    void show(ostream& os = std::cout) const;
};

