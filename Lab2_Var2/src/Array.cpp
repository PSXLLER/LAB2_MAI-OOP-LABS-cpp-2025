#include "Array.h"
#include <algorithm>

using std::max;

Array::Array()
    {
        data = nullptr;
        length = 0;
    }

Array::Array(const size_t& n, unsigned char t)
    {
        length = n;
        
        if(n == 0)
        {
            data = nullptr;
        }
        else
        {
            data = new unsigned char[n];
            
            for(size_t i = 0; i < n; i++)
            {
                data[i] = t;
            }

        }
    }

Array::Array(const initializer_list<unsigned char> &t)
    {
        length = t.size();

        if(length == 0)
        {
            data = nullptr;
        }
        else
        {
            data = new unsigned char[length];
            size_t i = 0;
            for (unsigned char value: t)
            {
                data[i++] = value;
            }
        }
    }

Array::Array(const string& t)
    {
        length = t.size();

        if(length == 0)
        {
            data = nullptr;
        }
        else
        {
            data = new unsigned char[length];
            for(size_t i = 0; i < length; i++)
            {
                data[i] = static_cast<unsigned char>(t[i]);
            }
        }
    }

Array::Array(const Array& other)
    {
        length = other.length;

        if(length == 0)
        {
            data = nullptr;
        }
        else
        {
            data = new unsigned char[length];
            for(size_t i = 0; i < length; i++)
            {
                data[i] = other.data[i];
            } 
        }
    }

Array::Array(Array&& other) noexcept
    {
        length = other.length;
        data = other.data;

        other.length = 0;
        other.data = nullptr; 
    }

Array::~Array() noexcept
    {
        delete[] data;
    }

Array& Array::operator=(const Array& other)
{
    if (this != &other)
    {
        delete[] data; // очищаем старые данные

        length = other.length;
        if (length == 0)
        {
            data = nullptr;
        }
        else
        {
            data = new unsigned char[length];
            for (size_t i = 0; i < length; ++i)
            {
                data[i] = other.data[i];
            }
        }
    }
    return *this;
}

Array& Array::operator=(Array&& other) noexcept
{
    if (this != &other)
    {
        delete[] data;

        data = other.data;
        length = other.length;

        other.data = nullptr;
        other.length = 0;
    }
    return *this;
}


size_t Array::size() const
    {
        return length;
    }

unsigned char Array::ar(size_t i) const
    {
        if(i >= length)
        {
            throw out_of_range("Index out of range!!! Please enter another one.");
        }
        return data[i];
    }

Array Array::add(const Array& other) const
    {
        if(length != other.length)
        {
            throw invalid_argument("Arrays cannot be added together!!! Their lengths are different. Please try other arrays.");
        }
        Array result(length);

        for(size_t i = 0; i < length; i++)
        {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

Array Array::sub(const Array& other) const
    {
        if(length != other.length)
        {
            throw invalid_argument("Arrays cannot be subtracted!!! Their lengths are different. Please try other arrays.");
        }
        Array result(length);

        for(size_t i = 0; i < length; i++)
        {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

bool Array::equal(const Array& other) const
    {
        if(length != other.length)
        {
            return false;
        }
        else
        {
            for(size_t i = 0; i < length; i++)
            {
                if(data[i] != other.data[i])
                {
                    return false;
                }
            }
            return true;
        }
    }

bool Array::less(const Array& other) const
    {
        
        size_t min_length {0};
        
        if(length < other.length)
        {
            min_length = length;
        }
        else
        {
            min_length = other.length;
        }
        for (size_t i = 0; i < min_length; i++)
        {
            size_t idx = min_length - 1 - i;
            if(data[idx] < other.data[idx])
            {
                return true;
            }
            if(data[idx] > other.data[idx])
            {
                return false;
            }
        
        }
        return length < other.length;
    }

bool Array::greater(const Array& other) const
    {
        return !less(other) && !equal(other);
    }

void Array::print(ostream& os) const
    {
        os << "[";

        for(size_t i = 0; i < length; i++)
        {
            os << (int)data[i];
            if((i + 1) < length)
            {
                os << ", ";
            }
        }
        os << "]";
    }

void Array::set(size_t i, unsigned char v)
    {
        if(i >= length)
        {
            throw out_of_range("Index out of range!!! Please enter another one.");
        }
        data[i] = v;
    }
