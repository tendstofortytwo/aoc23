#include <fmt/core.h>
#include <string>
#include <iostream>

int main() {
	std::string line;

	int sum = 0;

	while(std::getline(std::cin, line)) {
		fmt::println("{}", line);
	}
}
