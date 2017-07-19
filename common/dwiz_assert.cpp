#include "dwiz_assert.h"
#include <sstream>

namespace dwiz
{
void assert(
    bool const f_expr,
    char const* const f_expr_string,
    char const* const f_file,
    int const f_line,
    char const* const f_func)
{
    if (!f_expr)
    {
        std::stringstream ss;
        ss << f_file << ":" << f_line << " (" << f_func << "): " << f_expr_string << ".";
        throw AssertError(ss.str());
    }
}

AssertError::AssertError(std::string const f_message)
    : m_message(f_message)
{
}

std::string const& AssertError::what() const
{
    return m_message;
}
} // namespace dwiz
