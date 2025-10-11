#pragma once

#include <iostream>
#include <initializer_list>
#include <cstddef>
#include <stdexcept>
#include <string>

using std::initializer_list;
using std::string;
using std::out_of_range;
using std::invalid_argument;
using std::ostream;
using std::cout;

class Array
{
    private:
    unsigned char* data;
    size_t length;

    public:
    Array();
    Array(const size_t& n, unsigned char t = 0);
    Array(const initializer_list<unsigned char> &t);
    Array(const string& t);
    Array(const Array& other);
    Array(Array&& other) noexcept;
    virtual ~Array() noexcept;

    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    size_t size() const;
    unsigned char ar(size_t i) const;
    Array add(const Array& other) const;
    Array sub(const Array& other) const;
    bool equal(const Array& other) const;
    bool less(const Array& other) const;
    bool greater(const Array& other) const;
    void print(ostream& os = cout) const;
    void set(size_t i, unsigned char v);
};