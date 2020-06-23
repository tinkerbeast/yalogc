#ifndef YALOG_ARGS_H_
#define YALOG_ARGS_H_

#if __cplusplus < 201700
#  error "C++17 or better is required"
#endif

#include "traits.h"

#include <type_traits>


#define ARGS_ESTIMATE_CHARSTR_SIZE 128
#define ARGS_ESTIMATE_UNKNOWN_SIZE 128
#define ARGS_ESTIMATE_ARITHMETIC_FACTOR 2  // 4 byte integer represented as 8 byte hex string
#define ARGS_ESTIMATE_SAFETY_BUFFER 32

namespace yalog::args {

static inline constexpr
uint16_t estimate_size() noexcept {
    return 0;
}

// arithmetic types

template<typename ArithmeticT, 
    typename std::enable_if<std::is_arithmetic<ArithmeticT>::value>::type* = nullptr,
    typename... Args>
static inline constexpr
uint16_t estimate_size(ArithmeticT , Args... args) {
    return static_cast<uint16_t>(sizeof(ArithmeticT)) * ARGS_ESTIMATE_ARITHMETIC_FACTOR 
        + estimate_size(args...);
}

// string, string_view

template<typename StringT, 
    typename std::enable_if<yalog::traits::is_stringlike<StringT>::value>::type* = nullptr,
    typename... Args>
static inline constexpr
uint16_t estimate_size(const StringT& first_arg, Args... args) {
    return static_cast<uint16_t>(first_arg.length() * sizeof(typename StringT::value_type))
            + estimate_size(args...);
}

// char* or char[]
// TODO: why does std formatter have specialisation for CharT* and const CharT*

template<typename CharT, 
    typename std::enable_if<yalog::traits::is_char<CharT>::value>::type* = nullptr,
    typename... Args>
static inline constexpr
uint16_t estimate_size(const CharT* , Args... args) {
    return static_cast<uint16_t>(ARGS_ESTIMATE_CHARSTR_SIZE * sizeof(CharT))
            + estimate_size(args...);
}

template<typename CharT, 
    std::size_t N,
    typename std::enable_if<yalog::traits::is_char<CharT>::value>::type* = nullptr,
    typename... Args>
static inline constexpr
uint16_t estimate_size(const CharT[N] , Args... args) {
    return static_cast<uint16_t>(ARGS_ESTIMATE_CHARSTR_SIZE * sizeof(CharT))
            + estimate_size(args...);
}

// nullptr, void*
// TODO: why does std formatter have specialisation for void* and const void*

template<typename... Args> 
static inline constexpr
uint16_t estimate_size(std::nullptr_t, Args... args) noexcept {
    return static_cast<uint16_t>(sizeof(void*) * ARGS_ESTIMATE_ARITHMETIC_FACTOR)
            + estimate_size(args...);
}

template<typename... Args> 
static inline constexpr
uint16_t estimate_size(const void*, Args... args) noexcept {
    return static_cast<uint16_t>(sizeof(void*) * ARGS_ESTIMATE_ARITHMETIC_FACTOR)
            + estimate_size(args...);
}

} // namespace yalog::args

#endif // YALOG_ARGS_H_

