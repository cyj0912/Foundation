#pragma once
#include <stdexcept>
namespace tc
{

class FNonCopyable
{
protected:
    constexpr FNonCopyable() = default;
    ~FNonCopyable() = default;

private:
    FNonCopyable(const FNonCopyable&) = delete;
    void operator=(const FNonCopyable&) = delete;
};

class not_implemented_exception : public std::logic_error
{
public:
    explicit not_implemented_exception(const std::string& _Message)
        : logic_error(_Message)
    {
    }

    explicit not_implemented_exception(const char* _Message)
        : logic_error(_Message)
    {
    }

    char const* what() const noexcept override { return "Function not yet implemented."; }
};

template <typename E> constexpr typename std::underlying_type<E>::type to_underlying(E e)
{
    return static_cast<typename std::underlying_type<E>::type>(e);
}

}
