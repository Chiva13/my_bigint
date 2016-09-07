#pragma once

#include <bigint.hpp>

#define TEST_EQUAL(X,Y) do { if ((X) != (Y)) { \
	std::cout \
		<< "Test fail: " << #X << " != " << #Y << " => " << (X) << " != " << (Y) << std::endl \
		<< "          at file " << __FILE__ << ":" << __LINE__ << std::endl; \
} } while(false)

int main() {
	//  Проверка инициализации
	{
		BigInt a("123");
		TEST_EQUAL(a.get_array()[0], 123);
		TEST_EQUAL(a.get_array()[0], 456);
	}

	{
		BigInt a("123456");
		if (a.get_array()[0] != 3456) {
			std::cout << "Value mismatch." << std::endl;
		}
		if (a.get_array()[1] != 12) {
			std::cout << "Value mismatch." << std::endl;
		}
	}
	//Проверка вычитания

	BigInt a("12123123123435435");


	std::cout << "a=" << a << std::endl;
	BigInt b("12343");
	std::cout << "b=" << b << std::endl;
	std::cout << "->" << a - b << std::endl;
	return 0;
}