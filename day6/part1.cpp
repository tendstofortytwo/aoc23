#include <fmt/core.h>
#include <string>
#include <iostream>
#include <string_view>
#include <ranges>
#include <charconv>
#include <vector>

using std::operator""sv;

std::vector<long> readLine() {
	std::string line;
	std::vector<long> res;
	std::getline(std::cin, line);
	line = line.substr(9);
	for(const auto& nView : std::views::split(line, ' ')) {
		if(nView.empty()) continue;
		std::string_view nStr(nView);
		
		long num;
		std::from_chars(nStr.begin(), nStr.end(), num);
		res.push_back(num);
	}
	return res;
}

int main() {
	auto times = readLine();
	auto dists = readLine();

	long prod = 1;

	for(long i = 0; i < times.size(); ++i) {
		long ways = 0;
		for(long c = 1; c < times[i]; ++c) {
			if(times[i] * c - c*c > dists[i]) {
				++ways;
			}
		}
		prod *= ways;
		fmt::println("{}", ways);
	}

	fmt::println("{}", prod);
}
