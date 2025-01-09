#ifndef MINSTL_TYPE_TRAITS_H
#define MINSTL_TYPE_TRAITS_H

// 用于提取类型信息
#include <type_traits>

namespace minstl
{
    template <typename T, T v>
    class m_integral_constant
    {
    public:
        static constexpr T value = v;
    };

    template <bool b>
    using m_bool_constant = m_integral_constant<bool, b>;

    using m_true_type = m_bool_constant<true>;
    using m_false_type = m_bool_constant<false>;

    template <typename T1, typename T2>
    class pair;

    template <typename T>
    class is_pair : public m_false_type
    {
    };

    template <typename T1, typename T2>
    class is_pair<minstl::pair<T1, T2>> : public m_true_type
    {
    };
}

#endif // !MINSTL_TYPE_TRAITS_H