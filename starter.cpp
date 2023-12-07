#include <fmt/core.h>
#include <bits/stdc++.h>

using std::operator""sv;

int main() {
	std::string lineStr;

	while(std::getline(std::cin, lineStr)) {
		std::string_view line(lineStr);
		fmt::println("{}", line);
	}
}
