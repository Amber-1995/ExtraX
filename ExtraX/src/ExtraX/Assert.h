#pragma once
#ifndef EXTRAX_ASSERT_H
#define EXTRAX_ASSERT_H

#include <ExtraX/Common.h>
#include <ExtraX/Log.h>



#ifdef _DEBUG

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define XX_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { XX##type##ERROR(msg, __VA_ARGS__); XX_DEBUGBREAK(); } }
#define XX_INTERNAL_ASSERT_WITH_MSG(type, check, ...) XX_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define XX_INTERNAL_ASSERT_NO_MSG(type, check) XX_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", XX_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define XX_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define XX_INTERNAL_ASSERT_GET_MACRO(...) XX_EXPAND_MACRO( XX_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, XX_INTERNAL_ASSERT_WITH_MSG, XX_INTERNAL_ASSERT_NO_MSG))

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define XX_ASSERT(...) XX_EXPAND_MACRO( XX_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__))
#define XX_CORE_ASSERT(...) XX_EXPAND_MACRO( XX_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__))
#else
#define XX_ASSERT(...)
#define XX_CORE_ASSERT(...)
#endif










#endif //!EXTRAX_ASSERT_H
