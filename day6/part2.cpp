#include <fmt/core.h>
#include <string>
#include <iostream>
#include <ranges>
#include <charconv>
#include <vector>
#include <cmath>

double readLine() {
	std::string line;
	std::string number;
	std::getline(std::cin, line);
	line = line.substr(9);
	for(const auto& nView : std::views::split(line, ' ')) {
		if(nView.empty()) continue;
		std::string_view nStr(nView);
		number += nStr;
	}
	double res;
	std::from_chars(number.data(), number.data() + number.size(), res);
	return res;
}

int main() {
	double time = readLine();
	double dist = readLine();

	fmt::println("{} {}", time, dist);

	double mid = time / 2;
	double diff = std::sqrt(time*time - 4*dist) / 2;
	double min = mid - diff;
	double max = mid + diff;
	double ways = std::floor(max) - std::floor(min);

	fmt::println("{}", ways);
}
