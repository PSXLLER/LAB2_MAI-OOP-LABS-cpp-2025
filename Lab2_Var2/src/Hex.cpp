#include "Hex.h"
#include <algorithm>
#include <utility>
#include <stdexcept>
using namespace std;

unsigned char Hex::toVal(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
    if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
    throw invalid_argument("bad char");
}

char Hex::toChr(unsigned char v) {
    if (v < 10) return v + '0';
    if (v < 16) return v - 10 + 'A';
    throw invalid_argument("bad digit");
}

Hex::Hex() : digits(1, 0) {}

Hex::Hex(const Hex& h) : digits(h.digits) {}

Hex::Hex(Hex&& h) noexcept : digits(std::move(h.digits)) {}

Hex::Hex(const string& s) {
    if (s.empty()) throw invalid_argument("empty");
    size_t n = s.size();
    Array tmp(n);
    for (size_t i = 0; i < n; ++i)
        tmp.set(i, toVal(s[n - 1 - i]));
    digits = tmp;
}

Hex::Hex(std::initializer_list<unsigned char> t) : digits(t) {}

Hex::Hex(const Array& a) : digits(a) {}

Hex::~Hex() noexcept = default;

Hex& Hex::operator=(const Hex& other)
{
    if (this == &other) return *this;
    digits = other.digits;
    return *this;
}

Hex& Hex::operator=(Hex&& other) noexcept
{
    if (this == &other) return *this;
    digits = std::move(other.digits);
    return *this;
}


size_t Hex::size() const { return digits.size(); }

string Hex::toString() const {
    string s;
    for (size_t i = 0; i < digits.size(); ++i)
        s = toChr(digits.at(i)) + s;
    return s;
}

Hex Hex::add(const Hex& h) const {
    size_t n = std::max(digits.size(), h.digits.size());
    Array res(n + 1, 0);
    unsigned char carry = 0;
    for (size_t i = 0; i < n; ++i) {
        unsigned char a = i < digits.size() ? digits.at(i) : 0;
        unsigned char b = i < h.digits.size() ? h.digits.at(i) : 0;
        unsigned char sum = a + b + carry;
        res.set(i, sum % 16);
        carry = sum / 16;
    }
    if (carry) res.set(n, carry);
    size_t k = n + (carry ? 1 : 0);
    while (k > 1 && res.at(k - 1) == 0) --k;
    Array trim(k);
    for (size_t i = 0; i < k; ++i) trim.set(i, res.at(i));
    return Hex(trim);
}

Hex Hex::sub(const Hex& h) const {
    if (digits.size() < h.digits.size()) throw invalid_argument("neg result");
    if (digits.size() == h.digits.size() && digits.less(h.digits))
        throw invalid_argument("neg result");

    size_t n = digits.size();
    Array res(n, 0);
    unsigned char borrow = 0;
    for (size_t i = 0; i < n; ++i) {
        int a = digits.at(i);
        int b = i < h.digits.size() ? h.digits.at(i) : 0;
        int d = a - b - borrow;
        if (d < 0) { d += 16; borrow = 1; } else borrow = 0;
        res.set(i, static_cast<unsigned char>(d));
    }
    size_t k = n;
    while (k > 1 && res.at(k - 1) == 0) --k;
    Array trim(k);
    for (size_t i = 0; i < k; ++i) trim.set(i, res.at(i));
    return Hex(trim);
}

Hex Hex::copy() const { return Hex(digits); }

bool Hex::eq(const Hex& h) const { return digits.eq(h.digits); }
bool Hex::less(const Hex& h) const { return digits.less(h.digits); }
bool Hex::greater(const Hex& h) const { return digits.greater(h.digits); }

void Hex::print(ostream& os) const { os << toString(); }

void Hex::add_a(const Hex& h) { *this = add(h); }
void Hex::sub_a(const Hex& h) { *this = sub(h); }
void Hex::copy_a(const Hex& h) { *this = Hex(h.digits); }
