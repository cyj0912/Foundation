#pragma once
#include <iostream>

namespace tc
{

class ConstString
{
	const char* Ptr;
	std::size_t Sz;
public:
	template<std::size_t N>
	constexpr ConstString(const char(&a)[N]) : Ptr(a), Sz(N) {}

	constexpr ConstString(const char* a, size_t n) : Ptr(a), Sz(n) {}

	constexpr char operator[](size_t n) const
	{
		return n < Sz ? Ptr[n] : throw std::out_of_range("constexpr string out of range");
	}

	constexpr size_t size() const
	{
		return Sz;
	}
};

constexpr uint32_t SDBMHashChar(uint32_t hash, unsigned char c)
{
	//Cast to unsigned long long to avoid compiler warning about int overflow
	return c + (static_cast<unsigned long long>(hash) << 6) + (hash << 16) - hash;
}

constexpr uint32_t ConstStrHash(ConstString s, size_t n = 0, uint32_t hash = 0)
{
	return (n == s.size() || !s[n]) ? hash : ConstStrHash(s, n + 1, SDBMHashChar(hash, s[n]));
}

template <uint32_t N>
struct PrintConstHash
{
	PrintConstHash()
	{
		printf("%08X\n", N);
	}
};

}

//Put the hash operator in anonymous namespace to avoid annoying using directives
constexpr uint32_t operator "" _hash(const char* str, size_t len)
{
	return tc::ConstStrHash(tc::ConstString(str, len));
}