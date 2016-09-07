#pragma once

#include <iostream>
#include <array>
#include <string>
#include <sstream>
#include <iomanip>

class BigInt {
public:
	int len = 1;
	static const int N = 10;
	static const int array_size = 40;
	using store_t = int16_t;
	BigInt() {
		value = { 0 };
		length = 1;
	}
	BigInt(const std::string& value) {
		// перевод из 10чной системы счисления
		int current = 0;
		for (ptrdiff_t i = value.size() - 1; i >= 0; i -= len)
		{
			int start = i - len + 1;
			if (start < 0) start = 0;
			std::string val = value.substr(start, i - start + 1);
			this->value[current++] = atoi(val.c_str());
		}
		length = current;
		for (ptrdiff_t i = length; i < array_size; i++) {
			this->value[i] = 0;
		}
	}
	std::string string() const {
		// Перевод в десятичную систему счисления...
		std::stringstream  res;
		res << value[length - 1];
		for (ptrdiff_t i = length - 2; i >= 0; i--)
			res << std::setprecision(1) << std::setfill('0') << std::setw(len) << value[i];
		return res.str();
	}
	friend bool operator<=(const BigInt& a, const BigInt& b);
	friend BigInt operator-(const BigInt& a, const BigInt& b);
	friend BigInt operator*(const BigInt& a, const BigInt& b);
	friend BigInt operator*(const BigInt& a, const int& n);
private:
	std::array<store_t, array_size> value;
	store_t length;
};

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