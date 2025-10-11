#include "Array.h"
#include <algorithm>
#include <utility>
using namespace std;

Array::Array(): data(nullptr), len(0) {}

Array::Array(size_t n, unsigned char v) {
    len = n;
    if (!n) { data = nullptr; return; }
    data = new unsigned char[n];
    for (size_t i = 0; i < n; ++i) data[i] = v;
}

Array::Array(initializer_list<unsigned char> t) {
    len = t.size();
    data = len ? new unsigned char[len] : nullptr;
    size_t i = 0;
    for (auto x : t) data[i++] = x;
}

Array::Array(const string& s) {
    len = s.size();
    data = len ? new unsigned char[len] : nullptr;
    for (size_t i = 0; i < len; ++i)
        data[i] = static_cast<unsigned char>(s[i]);
}

Array::Array(const Array& a) {
    len = a.len;
    data = len ? new unsigned char[len] : nullptr;
    if (data) std::copy(a.data, a.data + len, data);
}

Array::Array(Array&& a) noexcept {
    data = a.data;
    len = a.len;
    a.data = nullptr;
    a.len = 0;
}

Array::~Array() noexcept { delete[] data; }

Array& Array::operator=(const Array& a) {
    if (this == &a) return *this;
    delete[] data;
    len = a.len;
    data = len ? new unsigned char[len] : nullptr;
    if (data) copy(a.data, a.data + len, data);
    return *this;
}

Array& Array::operator=(Array&& a) noexcept {
    if (this == &a) return *this;
    delete[] data;
    data = a.data;
    len = a.len;
    a.data = nullptr;
    a.len = 0;
    return *this;
}

size_t Array::size() const { return len; }

unsigned char Array::at(size_t i) const {
    if (i >= len) throw out_of_range("bad index");
    return data[i];
}

Array Array::add(const Array& other) const {
    if (len != other.len) throw invalid_argument("len mismatch");
    Array r(len);
    for (size_t i = 0; i < len; ++i) r.data[i] = data[i] + other.data[i];
    return r;
}

Array Array::sub(const Array& other) const {
    if (len != other.len) throw invalid_argument("len mismatch");
    Array r(len);
    for (size_t i = 0; i < len; ++i) r.data[i] = data[i] - other.data[i];
    return r;
}

bool Array::eq(const Array& other) const {
    if (len != other.len) return false;
    for (size_t i = 0; i < len; ++i)
        if (data[i] != other.data[i]) return false;
    return true;
}

bool Array::less(const Array& other) const {
    size_t m = std::min(len, other.len);
    for (size_t i = 0; i < m; ++i) {
        size_t k = m - 1 - i;
        if (data[k] < other.data[k]) return true;
        if (data[k] > other.data[k]) return false;
    }
    return len < other.len;
}

bool Array::greater(const Array& other) const {
    return !eq(other) && !less(other);
}

void Array::set(size_t i, unsigned char v) {
    if (i >= len) throw out_of_range("bad index");
    data[i] = v;
}

void Array::show(ostream& os) const {
    os << "[";
    for (size_t i = 0; i < len; ++i) {
        os << int(data[i]);
        if (i + 1 < len) os << ",";
    }
    os << "]";
}