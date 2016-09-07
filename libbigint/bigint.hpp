#pragma once

#include <iostream>
#include <array>
#include <string>
#include <sstream>
#include <iomanip>

class BigInt {
public:
	int len = 4;
	static const int N = 10000;
	static const int array_size = 6;
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

	std::array<store_t, array_size>&  get_array() { return value; }

	friend bool operator<=(const BigInt& a, const BigInt& b);
	friend BigInt operator-(const BigInt& a, const BigInt& b);
	friend BigInt operator*(const BigInt& a, const BigInt& b);
	friend BigInt operator*(const BigInt& a, const int& n);
private:
	std::array<store_t, array_size> value;
	store_t length;
};

bool operator<=(const BigInt& a, const BigInt& b);
BigInt operator-(const BigInt& a, const BigInt& b);
BigInt operator*(const BigInt& a, const BigInt& b);
BigInt operator*(const BigInt &a, const int& n);
std::ostream& operator<<(std::ostream& os, const BigInt& v);
