#ifndef DWIZ_COMMON_ASSERT_H
#define DWIZ_COMMON_ASSERT_H

#include <common/dwiz_std.h>
#include <string>

namespace dwiz
{
    class AssertError
    {
    public:
        AssertError(std::string const f_message);
        std::string const& what() const;
    private:
        std::string const m_message;
    };

    void assert(
            bool const f_expr,
            char const* const f_expr_string,
            char const* const f_file,
            int const f_line,
            char const* const f_func
    );

#ifdef DWIZ_DEBUG
#define DWIZASSERT(f_expr) \
    assert(f_expr, #f_expr, __FILE__, __LINE__, __func__)
#else
#define DWIZASSERT(expr)
#endif
}  // namespace dwiz

#endif
