#ifndef MINSTL_FUNCTIONAL_H
#define MINSTL_FUNCTIONAL_H

namespace minstl
{

    template <typename Arg, typename Result>
    class unarg_function
    {
    public:
        using argument_type = Arg;
        using result_type = Result;
    };

    template <typename Arg1, typename Arg2, typename Result>
    class binary_function
    {
    public:
        using first_argument_type = Arg1;
        using second_argument_type = Arg2;
        using result_type = Result;
    };

    template <typename T>
    class plus : public binary_function<T, T, T>
    {
    public:
        T operator()(const T &x, const T &y) const { return x + y; }
    };

    template <typename T>
    class minus : public binary_function<T, T, T>
    {
    public:
        T operator()(const T &x, const T &y) const { return x - y; }
    };

    template <typename T>
    class multiplies : public binary_function<T, T, T>
    {
    public:
        T operator()(const T &x, const T &y) const { return x * y; }
    };

    template <typename T>
    class divides : public binary_function<T, T, T>
    {
    public:
        T operator()(const T &x, const T &y) const { return x / y; }
    };

    template <typename T>
    class modulus : public binary_function<T, T, T>
    {
    public:
        T operator()(const T &x, const T &y) const { return x % y; }
    };

    template <typename T>
    class negate : public unarg_function<T, T>
    {
    public:
        T operator()(const T &x) const { return -x; }
    };

    template <typename T>
    T identity_element(plus<T> dummy) { return T(0); }

}

#endif // !MINSTL_FUNCTIONAL_H