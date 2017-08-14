#ifndef DWIZ_COMMON_DWIZ_STD_H
#define DWIZ_COMMON_DWIZ_STD_H

#define DWIZ_UNUSED(x) (void) (x)

#ifndef __has_cpp_attribute
#define __has_cpp_attribute(name) 0
#endif

// The DWIZ_WARN_UNUSED_RESULT definition can be used in front of a function. It is a hint to the
// compiler to warn if callers do not use the returned value.
// Example usage:
// DWIZ_WARN_UNUSED_RESULT int foo() { return 0; }
#if __has_cpp_attribute(nodiscard)
#define DWIZ_WARN_UNUSED_RESULT [[nodiscard]]
#elif __has_cpp_attribute(gnu::warn_unused_result)
#define DWIZ_WARN_UNUSED_RESULT [[gnu::warn_unused_result]]
#else
#define DWIZ_WARN_UNUSED_RESULT
#endif

#endif
