#include <fmt/core.h>
#include <string>
#include <iostream>
#include <unordered_map>
#include <string_view>

std::unordered_map<std::string_view, int> numbers {
	{ "zero", 0 },
	{ "one", 1 },
	{ "two", 2 },
	{ "three", 3 },
	{ "four", 4 },
	{ "five", 5 },
	{ "six", 6 },
	{ "seven", 7 },
	{ "eight", 8 },
	{ "nine", 9 },
};

int main() {
	std::string line;

	int sum = 0;

	while(std::getline(std::cin, line)) {
		int i, start = 0, end = 0;
		int startIdx = line.size(), endIdx = -1;
		for(i = 0; i < line.size(); ++i) {
			if(line[i] >= '0' && line[i] <= '9') {
				start = line[i] - '0';
				startIdx = i;
				fmt::println("start now {} {}", start, startIdx);
				break;
			}
		}
		for(i = line.size() - 1; i >= 0; --i) {
			if(line[i] >= '0' && line[i] <= '9') {
				end = line[i] - '0';
				endIdx = i;
				fmt::println("end now {} {}", end, endIdx);
				break;
			}
		}
		for(auto& [str, val] : numbers) {
			int f = line.find(str);
			if(f != std::string::npos && f < startIdx) {
				start = val;
				startIdx = f;
				fmt::println("start now {} {}", start, startIdx);
			}
			int rf = line.rfind(str);
			if(rf != std::string::npos && rf > endIdx) {
				end = val;
				endIdx = rf;
				fmt::println("end now {} {}", end, endIdx);
			}
		}
		int n = start*10 + end;
		fmt::println("{} {} {}", start, end, n);
		sum += n;
	}

	fmt::println("{}", sum);
}
