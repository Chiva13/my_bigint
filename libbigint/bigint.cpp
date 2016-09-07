#include "bigint.hpp"

bool operator<=(const BigInt& a, const BigInt& b)
{
	if (a.length != b.length)
		return a.length < b.length;
	for (size_t i = a.length - 1; i >= 0; i--) {
		if (a.value[i] != b.value[i])
			return a.value[i] < b.value[i];
	}
	return true;
}

BigInt operator-(const BigInt& a, const BigInt& b) {
	BigInt res = a;
	int r = 0;
	for (size_t i = 0; i < res.length; i++)
	{
		res.value[i] -= b.value[i] + r;
		if (res.value[i] < 0)
		{
			res.value[i] += BigInt::N;
			r = 1;
		}
		else
			r = 0;
	}
	if (!res.value[res.length - 1] && res.length != 1)
		res.length--;
	return res;
}

BigInt operator*(const BigInt& a, const BigInt& b)
{
	BigInt res;
	for (size_t i = 0; i < a.length; i++)
	{
		int r = 0;
		for (size_t j = 0; j < b.length | r; j++)
		{
			res.value[i + j] += a.value[i] * b.value[j] + r;
			r = res.value[i + j] / BigInt::N;
			res.value[i + j] -= r*BigInt::N;
		}
	}
	int pos = a.length + b.length;
	while (pos > 0 && !res.value[pos])
		pos--;
	res.length = pos + 1;
	return res;
}

BigInt operator*(const BigInt &a, const int& n)
{
	BigInt res;
	res.length = a.length;
	int r = 0;
	for (size_t i = 0; i < res.length | r; i++)
	{
		res.value[i] = a.value[i] * n + r;
		r = res.value[i] / BigInt::N;
		res.value[i] -= r * BigInt::N;
	}
	if (res.value[res.length])
		res.length++;
	return res;
}

std::ostream& operator<<(std::ostream& os, const BigInt& v)
{
	os << v.string();
	return os;
}