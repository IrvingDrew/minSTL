#ifndef MINSTL_EXCEPTDEF_H
#define MINSTL_EXCEPTDEF_H

#include <stdexcept>
#include <cassert>

namespace minstl
{

#define MINSTL_DEBUG(expr) assert(expr)

#define THROW_LENGTH_ERROR_IF(expr, what)  \
    do                                     \
    {                                      \
        if (expr)                          \
        {                                  \
            throw std::length_error(what); \
        }                                  \
    } while (0)

#define THROW_OUT_OF_RANGE_IF(expr, what)  \
    do                                     \
    {                                      \
        if (expr)                          \
        {                                  \
            throw std::out_of_range(what); \
        }                                  \
    } while (0)

#define THROW_RUNTIME_ERROR_IF(expr, what)  \
    do                                      \
    {                                       \
        if (expr)                           \
        {                                   \
            throw std::runtime_error(what); \
        }                                   \
    } while (0)

}

#endif // !MINSTL_EXCEPTDEF_H