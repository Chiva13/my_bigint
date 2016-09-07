#pragma once

#include <bigint.hpp>

int main() {
	// your code goes here
	BigInt a("12123123123435435");
	std::cout << "a=" << a << std::endl;
	BigInt b("12343");
	std::cout << "b=" << b << std::endl;
	std::cout << "->" << a - b << std::endl;
	return 0;
}