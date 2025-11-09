#include "Hex.h"
#include <algorithm>
#include <utility>


using std::max;
using std::move;

unsigned char Hex::CharToHex(char c)
    {
        if(c >= '0' && c <= '9')
        {
            return c - '0';
        }

        if(c >= 'A' && c <= 'F')
        {
            return 10 + (c - 'A');
        }

        if(c >= 'a' && c <= 'f')
        {
            return 10 + (c - 'a');
        }

        throw invalid_argument("Invalid character in hexadecimal number!!! Please enter another one.");
    }

char Hex::HexToChar(unsigned char v)
    {
        if(v < 10)
        {
            return v + '0';
        }

        if(v < 16)
        {
            return (v - 10) + 'A';
        }    
        
        throw invalid_argument("Invalid hexadecimal digit!!! Please enter another one.");
    }
    
Hex::Hex()
    {
        digits = Array(1, 0);
    }

Hex::Hex(const Hex& other)
    {
        digits = Array(other.digits);
    }

Hex::Hex(Hex&& other) noexcept
    {
        digits = move(other.digits);
    }

Hex::Hex(const string& str)
    {
        if(str.empty())
        {
            throw invalid_argument("Empty line when creating!!! Please enter another one.");
        }

        size_t n = str.size();
        digits = Array(n);
        for(size_t i = 0; i < n; i++)
        {
            unsigned char v = CharToHex(str[n - 1 - i]);
            digits.set(i, v);
        }

    }

Hex::Hex(const initializer_list<unsigned char>& t)
    {
        digits = Array(t);
    }

Hex::Hex(const Array& arr)
    {
        digits = Array(arr);
    }

Hex::~Hex() noexcept
    {
        // Массив освободит память
    }

size_t Hex::size() const
    {
        return digits.size();
    }

string Hex::toString() const
    {
        string s;
        for (size_t i = 0; i < digits.size(); i++)
        {
            s = HexToChar(digits.ar(i)) + s;
        }
        return s;
    }
    
Hex Hex::add(const Hex& other) const
    {
        size_t MaxLen = max(digits.size(), other.digits.size());
        Array result(MaxLen + 1, 0);
        unsigned char carry = 0;

        for(size_t i = 0; i < MaxLen; i++)
        {
            unsigned char a = (i < digits.size()) ? digits.ar(i) : 0;
            unsigned char b = (i < other.digits.size()) ? other.digits.ar(i) : 0;

            unsigned char sum = a + b + carry;
            result.set(i, sum % 16);
            carry = sum / 16;
        }

        if(carry)
        {
            result.set(MaxLen, carry);
        }

        size_t newLen = MaxLen + (carry ? 1 : 0);
        while(newLen > 1 && result.ar(newLen - 1) == 0)
        {
        newLen--;
        }

        Array trimmed(newLen);
        for (size_t i = 0; i < newLen; i++)
        {
        trimmed.set(i, result.ar(i));
        }

    return Hex(trimmed);
}

Hex Hex::sub(const Hex& other) const
    {
        if (digits.size() < other.digits.size())
        throw invalid_argument("It is impossible to subtract a larger number from a smaller one!!! Please try another.");
        else if (digits.size() == other.digits.size())
        {
            bool strictlyLess = false;
            for (size_t i = digits.size(); i-- > 0; )
            {
                unsigned char a = digits.ar(i);
                unsigned char b = (i < other.digits.size()) ? other.digits.ar(i) : 0;
            if (a < b)
            {
                strictlyLess = true;
                break;
            }
            else if (a > b)
                break;
        }
        if (strictlyLess)
         throw invalid_argument("It is impossible to subtract a larger number from a smaller one!!! Please try another.");
    }
         

        size_t n = digits.size();
        Array result(n, 0);
        unsigned char borrow = 0;

        for(size_t i = 0; i < n; i++)
        {
            int a = digits.ar(i);
            int b = (i < other.digits.size()) ? other.digits.ar(i) : 0;
            int diff = a - b - borrow;

            if(diff < 0)
            {
                diff += 16;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }

            result.set(i, static_cast<unsigned char>(diff));
        }

        size_t newLen = n;
        
        while (newLen > 1 && result.ar(newLen - 1) == 0)
        {
            newLen--;
        }
        

        Array trimmed(newLen);
        for(size_t i = 0; i < newLen; i++)
        {
            trimmed.set(i, result.ar(i));
        }

        return Hex(trimmed);
}

Hex Hex::copy() const
    {
        return Hex(digits);
    }

bool Hex::equal(const Hex& other) const
    {
        return digits.equal(other.digits);
    }

bool Hex::less(const Hex& other) const
    {
        return digits.less(other.digits);
    }

bool Hex::greater(const Hex& other) const
    {
        return digits.greater(other.digits);
    }

void Hex::print(ostream& os) const
    {
        os << toString();
    }

void Hex::add_a(const Hex& other)
    {
        Hex temp = this->add(other);     
        digits = Array(temp.digits);     
    }

void Hex::sub_a(const Hex& other)
    {
        Hex temp = this->sub(other);
        digits = Array(temp.digits);
    }
    
void Hex::copy_a(const Hex& other)
    {
        digits = Array(other.digits);
    }