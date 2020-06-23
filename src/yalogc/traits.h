#ifndef YALOG_TRAITS_H_
#define YALOG_TRAITS_H_

#if __cplusplus < 201700
#  error "C++17 or better is required"
#endif

#include <string>
#include <string_view>

namespace yalog::traits {

// stringlike is string, string_view

template<typename T>
struct is_stringlike : std::false_type {};

template<typename CharT, typename Traits, typename Alloc>
struct is_stringlike<std::basic_string<CharT, Traits, Alloc>> : std::true_type {};

template<typename CharT, typename Traits>
struct is_stringlike<std::basic_string_view<CharT, Traits>> : std::true_type {};

// char is char or wchar_t
// TODO: char16_t, char32_t, char8_t

template<typename T>
struct is_char : std::false_type {};

template<>
struct is_char<char> : std::true_type {};

template<>
struct is_char<wchar_t> : std::true_type {};

} // namespace yalog::traits

#endif // YALOG_TRAITS_H_









