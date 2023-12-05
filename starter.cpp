#include <fmt/core.h>
#include <string>
#include <iostream>
#include <string_view>
#include <ranges>
#include <charconv>

using std::operator""sv;

int main() {
	std::string lineStr;

	while(std::getline(std::cin, lineStr)) {
		std::string_view line(lineStr);
		fmt::println("{}", line);
	}
}
