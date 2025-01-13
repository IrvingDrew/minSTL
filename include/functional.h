#ifndef MINSTL_FUNCTIONAL_H
#define MINSTL_FUNCTIONAL_H

#include <cstddef>

namespace minstl
{
    // 定义一元函数的参数型别和返回值型别
    template <typename Arg, typename Result>
    class unarg_function
    {
    public:
        using argument_type = Arg;
        using result_type = Result;
    };

    // 定义二元函数的参数型别的返回值型别
    template <typename Arg1, typename Arg2, typename Result>
    class binary_function
    {
    public:
        using first_argument_type = Arg1;
        using second_argument_type = Arg2;
        using result_type = Result;
    };

    // 函数对象：加法
    template <typename T>
    class plus : public binary_function<T, T, T>
    {
    public:
        T operator()(const T &x, const T &y) const { return x + y; }
    };

    // 函数对象：减法
    template <typename T>
    class minus : public binary_function<T, T, T>
    {
    public:
        T operator()(const T &x, const T &y) const { return x - y; }
    };

    // 函数对象：乘法
    template <typename T>
    class multiplies : public binary_function<T, T, T>
    {
    public:
        T operator()(const T &x, const T &y) const { return x * y; }
    };

    // 函数对象：除法
    template <typename T>
    class divides : public binary_function<T, T, T>
    {
    public:
        T operator()(const T &x, const T &y) const { return x / y; }
    };

    // 函数对象：模取
    template <typename T>
    class modulus : public binary_function<T, T, T>
    {
    public:
        T operator()(const T &x, const T &y) const { return x % y; }
    };

    // 函数对象：否定
    template <typename T>
    class negate : public unarg_function<T, T>
    {
    public:
        T operator()(const T &x) const { return -x; }
    };

    // 加法的证同元素
    template <typename T>
    T identity_element(plus<T> dummy) { return T(0); }

    // 乘法的证同元素
    template <typename T>
    T identity_element(multiplies<T> dummy) { return T(1); }

    // 函数对象：等于
    template <typename T>
    class equal_to : public binary_function<T, T, bool>
    {
    public:
        bool operator()(const T &x, const T &y) const { return x == y; }
    };

    // 函数对象：不等于
    template <typename T>
    class not_equal_to : public binary_function<T, T, bool>
    {
    public:
        bool operator()(const T &x, const T &y) const { return x != y; }
    };

    // 函数对象：大于
    template <typename T>
    class greater : public binary_function<T, T, bool>
    {
    public:
        bool operator()(const T &x, const T &y) const { return x > y; }
    };

    // 函数对象：小于
    template <typename T>
    class less : public binary_function<T, T, bool>
    {
    public:
        bool operator()(const T &x, const T &y) const { return x < y; }
    };

    // 函数对象：大于等于
    template <typename T>
    class greater_equal : public binary_function<T, T, bool>
    {
    public:
        bool operator()(const T &x, const T &y) const { return x >= y; }
    };

    // 函数对象：小于等于
    template <typename T>
    class less_equal : public binary_function<T, T, bool>
    {
    public:
        bool operator()(const T &x, const T &y) const { return x <= y; }
    };

    // 函数对象：逻辑与
    template <typename T>
    class logical_and : public binary_function<T, T, bool>
    {
    public:
        bool operator()(const T &x, const T &y) const { return x && y; }
    };

    // 函数对象：逻辑或
    template <typename T>
    class logical_or : public binary_function<T, T, bool>
    {
    public:
        bool operator()(const T &x, const T &y) const { return x || y; }
    };

    // 函数对象：逻辑非
    template <typename T>
    class logical_not : public unarg_function<T, bool>
    {
    public:
        bool operator()(const T &x) const { return !x; }
    };

    // 证同函数：不会改变元素，返回本身
    template <typename T>
    class identity : public unarg_function<T, bool>
    {
        const T &operator()(const T &x) const { return x; }
    };

    // 选择函数：接受一个 pair，返回第一个元素
    template <typename Pair>
    class selectfirst : public unarg_function<Pair, typename Pair::first_type>
    {
    public:
        const typename Pair::first_type &operator()(const Pair &x) const
        {
            return x.first;
        }
    };

    // 选择函数：接受一个 pair，返回第二个元素
    template <typename Pair>
    class selectsecond : public unarg_function<Pair, typename Pair::second_type>
    {
    public:
        const typename Pair::second_type &operator()(const Pair &x) const
        {
            return x.second;
        }
    };

    // 投射函数：返回第一参数
    template <typename Arg1, typename Arg2>
    class projectfirst : public binary_function<Arg1, Arg2, Arg1>
    {
    public:
        Arg1 operator()(const Arg1 &x, const Arg2 &y) { return x; }
    };

    // 投射函数：返回第二参数
    template <typename Arg1, typename Arg2>
    class projectsecond : public binary_function<Arg1, Arg2, Arg1>
    {
    public:
        Arg2 operator()(const Arg1 &x, const Arg2 &y) { return y; }
    };

    // 哈希函数对象
    template <typename Key>
    class hash
    {
    };

    template <typename T>
    class hash<T *>
    {
    public:
        size_t operator()(T *p) const noexcept
        {
            return reinterpret_cast<size_t>(p);
        }
    };

    template <>
    class hash<bool>
    {
    public:
        size_t operator()(bool val) const noexcept
        {
            return static_cast<size_t>(val);
        }
    };

    template <>
    class hash<char>
    {
    public:
        size_t operator()(char val) const noexcept
        {
            return static_cast<size_t>(val);
        }
    };

    template <>
    class hash<signed char>
    {
    public:
        size_t operator()(signed char val) const noexcept
        {
            return static_cast<size_t>(val);
        }
    };

    template <>
    class hash<unsigned char>
    {
    public:
        size_t operator()(unsigned char val) const noexcept
        {
            return static_cast<size_t>(val);
        }
    };
    template <>
    class hash<wchar_t>
    {
    public:
        size_t operator()(wchar_t val) const noexcept
        {
            return static_cast<size_t>(val);
        }
    };
    template <>
    class hash<char16_t>
    {
    public:
        size_t operator()(char16_t val) const noexcept
        {
            return static_cast<size_t>(val);
        }
    };
    template <>
    class hash<char32_t>
    {
    public:
        size_t operator()(char32_t val) const noexcept
        {
            return static_cast<size_t>(val);
        }
    };
    template <>
    class hash<short>
    {
    public:
        size_t operator()(short val) const noexcept
        {
            return static_cast<size_t>(val);
        }
    };
    template <>
    class hash<unsigned short>
    {
    public:
        size_t operator()(unsigned short val) const noexcept
        {
            return static_cast<size_t>(val);
        }
    };
    template <>
    class hash<int>
    {
    public:
        size_t operator()(int val) const noexcept
        {
            return static_cast<size_t>(val);
        }
    };
    template <>
    class hash<unsigned int>
    {
    public:
        size_t operator()(unsigned int val) const noexcept
        {
            return static_cast<size_t>(val);
        }
    };
    template <>
    class hash<long>
    {
    public:
        size_t operator()(long val) const noexcept
        {
            return static_cast<size_t>(val);
        }
    };
    template <>
    class hash<unsigned long>
    {
    public:
        size_t operator()(unsigned long val) const noexcept
        {
            return static_cast<size_t>(val);
        }
    };
    template <>
    class hash<long long>
    {
    public:
        size_t operator()(long long val) const noexcept
        {
            return static_cast<size_t>(val);
        }
    };

    template <>
    class hash<unsigned long long>
    {
    public:
        size_t operator()(unsigned long long val) const noexcept
        {
            return static_cast<size_t>(val);
        }
    };

    inline size_t bitwise_hash(const unsigned char *first, size_t count)
    {
#if (_MSC_VER && _WIN64) || ((__GNUC__ || __clang__) && __SIZEOF_POINTER__ == 8)
        const size_t fnv_offset = 14695981039346656037ull;
        const size_t fnv_prime = 1099511628211ull;
#else
        const size_t fnv_offset = 2166136261u;
        const size_t fnv_prime = 16777619u;
#endif
        size_t result = fnv_offset;
        for (size_t i = 0; i < count; ++i)
        {
            result ^= (size_t)first[i];
            result *= fnv_prime;
        }
        return result;
    }

    template <>
    class hash<float>
    {
    public:
        size_t operator()(const float &val)
        {
            return val == 0.0f ? 0 : bitwise_hash((const unsigned char *)&val, sizeof(float));
        }
    };

    template <>
    class hash<double>
    {
    public:
        size_t operator()(const double &val)
        {
            return val == 0.0f ? 0 : bitwise_hash((const unsigned char *)&val, sizeof(double));
        }
    };

    template <>
    class hash<long double>
    {
    public:
        size_t operator()(const long double &val)
        {
            return val == 0.0f ? 0 : bitwise_hash((const unsigned char *)&val, sizeof(long double));
        }
    };
}

#endif // !MINSTL_FUNCTIONAL_H